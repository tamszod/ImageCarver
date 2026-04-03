#pragma once

template<typename Ch>
void CRV_XMLCommon<Ch>::Parse(crv::type::ByteStream& stream) {
    _chstream = std::vector<Ch>(stream.begin(), stream.end());
    _chstream.push_back('\0');
    _xmlDocument->parse<0>(_chstream.data());
}

template<typename Ch>
rapidxml::xml_node<Ch>* CRV_XMLCommon<Ch>::FindRootNodeElement(const Ch* name) {
	return _xmlDocument->first_node(name);
}

template<typename Ch>
rapidxml::xml_node<Ch>* CRV_XMLCommon<Ch>::FindNodeElement(rapidxml::xml_node<char>* node, const Ch* name){
    return node->first_node(name);
}

template<typename Ch>
std::optional<Ch*> CRV_XMLCommon<Ch>::FindNodeElementValue(rapidxml::xml_node<char>* node, const Ch* name) {
    if (auto* child = node->first_node(name)) {
        if (auto* val = child->value(); val && val[0] != Ch('\0')) {
            return val;
        }
    }
    return std::nullopt;
}

template<typename Ch>
std::optional<int> CRV_XMLCommon<Ch>::FindNodeElementIntValue(rapidxml::xml_node<char>* node, const Ch* name) {
    if (auto val = FindNodeElementValue(node, name)) {
        try {
            return std::stoi(*val);
        }
        catch (const std::exception&) {
            return std::nullopt;
        }
    }
    return std::nullopt;
}

template<typename Ch>
std::optional<std::vector<PointF>> CRV_XMLCommon<Ch>::FindNodeElementPointFListValue(
    rapidxml::xml_node<char>* node, const Ch* name, const Ch* subname
) {
    if (auto* parent = node->first_node(name)) {

        std::vector<PointF> points;

        for (auto* child = parent->first_node(subname); child; child = child->next_sibling(subname)) {

            auto x = FindAttributeFloatValue(child, "x");
            auto y = FindAttributeFloatValue(child, "y");

            if (!x || !y) {
				return std::nullopt;
            }

            points.push_back(PointF{ *x, *y });
        }

        if (!points.empty()) {
            return points;
        }
    }

    return std::nullopt;
}

template<typename Ch>
std::optional<BoundingBoxF> CRV_XMLCommon<Ch>::FindNodeElementBoundingBoxFValue(rapidxml::xml_node<char>* node, const Ch* name) {
   if (auto* bbox = node->first_node(name)) {

        auto left = FindAttributeFloatValue(bbox, "left");
        auto top = FindAttributeFloatValue(bbox, "top");
        auto right = FindAttributeFloatValue(bbox, "right");
        auto bottom = FindAttributeFloatValue(bbox, "bottom");

        if (!left || !top || !right || !bottom) {
            return std::nullopt;
        }

        return BoundingBoxF{
            *left,
            *top,
            *right,
            *bottom
        };
    }

    return std::nullopt;
}

template<typename Ch>
std::optional<std::unique_ptr<CRV_Color>> CRV_XMLCommon<Ch>::FindNodeElementCRVColorValue(rapidxml::xml_node<char>* node, const Ch* name) {
    if (auto* colorNode = node->first_node(name)) {

        auto r = FindAttributeUINT8TValue(colorNode, "r");
        auto g = FindAttributeUINT8TValue(colorNode, "g");
        auto b = FindAttributeUINT8TValue(colorNode, "b");
        auto a = FindAttributeUINT8TValue(colorNode, "a"); // optional

        if (!r || !g || !b) {
            return std::nullopt;
        }

        if (a) {
            return CRV_Color::Create(*r, *g, *b, *a);
        }
        else {
            return CRV_Color::Create(*r, *g, *b);
        }
    }

    return std::nullopt;
}

template<typename Ch>
std::optional<int> CRV_XMLCommon<Ch>::FindAttributeIntValue(rapidxml::xml_node<char>* node, const Ch* name) {
    if (auto* attr = node->first_attribute(name)) {
        if (auto* val = attr->value(); val && val[0] != Ch('\0')) {
            try {
                return std::stoi(val);
            } catch (const std::exception&) {
                return std::nullopt;
            }
        }
	}
    return std::nullopt;
}

template<typename Ch>
std::optional<float> CRV_XMLCommon<Ch>::FindAttributeFloatValue(rapidxml::xml_node<char>* node, const Ch* name) {
    if (auto* attr = node->first_attribute(name)) {
        if (auto* val = attr->value(); val && val[0] != Ch('\0')) {
            try {
                return std::stof(val);
            }
            catch (const std::exception&) {
                return std::nullopt;
            }
        }
    }
    return std::nullopt;
}

template<typename Ch>
std::optional<uint8_t> CRV_XMLCommon<Ch>::FindAttributeUINT8TValue(rapidxml::xml_node<char>* node, const Ch* name) {
    if (auto* attr = node->first_attribute(name)) {
        if (auto* val = attr->value(); val && val[0] != Ch('\0')) {
            try {
                int result = std::stoi(val);

                // Range check for uint8_t
                if (result >= 0 && result <= 255) {
                    return static_cast<uint8_t>(result);
                }
            }
            catch (const std::exception&) {
                return std::nullopt;
            }
        }
    }
    return std::nullopt;
}

template<typename Ch>
std::optional<uint32_t> CRV_XMLCommon<Ch>::FindAttributeUINT32TValue(
    rapidxml::xml_node<char>* node,
    const Ch* name
) {
    if (auto* attr = node->first_attribute(name)) {
        if (auto* val = attr->value(); val && val[0] != Ch('\0')) {
            try {
                unsigned long result = std::stoul(val);

                // Ensure it fits into uint32_t
                if (result <= std::numeric_limits<uint32_t>::max()) {
                    return static_cast<uint32_t>(result);
                }
            }
            catch (const std::exception&) {
                return std::nullopt;
            }
        }
    }
    return std::nullopt;
}

template<typename Ch>
rapidxml::xml_node<Ch>* CRV_XMLCommon<Ch>::CreateNodeElement(const Ch* name) {
    return _xmlDocument->allocate_node(
        rapidxml::node_type::node_element,
        name
    );
}

template<typename Ch>
rapidxml::xml_node<Ch>* CRV_XMLCommon<Ch>::CreateNodeElement(const Ch* name, const Ch* value) {
    return _xmlDocument->allocate_node(
        rapidxml::node_type::node_element,
        name,
        _xmlDocument->allocate_string(value)
	);
}

template<typename Ch>
rapidxml::xml_node<Ch>* CRV_XMLCommon<Ch>::CreateNodeElement(const Ch* name, const BoundingBoxF& value) {
	auto* node = CreateNodeElement(name);
    AppendAttribute(node, "left", value.left);
    AppendAttribute(node, "top", value.top);
    AppendAttribute(node, "right", value.right);
    AppendAttribute(node, "bottom", value.bottom);
	return node;
}

template<typename Ch>
rapidxml::xml_node<Ch>* CRV_XMLCommon<Ch>::CreateNodeElement(const Ch* name, const CRV_Color& value) {
    auto* node = CreateNodeElement(name);
    AppendAttribute(node, "r", value.GetRValue());
    AppendAttribute(node, "g", value.GetGValue());
    AppendAttribute(node, "b", value.GetBValue());
    AppendAttribute(node, "a", value.GetAValue());
	return node;
}

template<typename Ch>
rapidxml::xml_node<Ch>* CRV_XMLCommon<Ch>::CreateNodeElement(const Ch* name, uint32_t value) {
    std::string temp = std::to_string(value);
    return _xmlDocument->allocate_node(
        rapidxml::node_type::node_element,
        name,
        _xmlDocument->allocate_string(temp.c_str())
    );
}

template<typename Ch>
rapidxml::xml_node<Ch>* CRV_XMLCommon<Ch>::CreateNodeElement(const Ch* name, const Ch* subname, std::vector<PointF> points) {
    auto* node = CreateNodeElement(name);
    for (size_t i = 0; i < points.size(); i++) {
        auto* subNode = CreateNodeElement(subname);
		AppendAttribute(subNode, "x", points[i].x);
		AppendAttribute(subNode, "y", points[i].y);
		node->append_node(subNode);
    }
	return node;
}

template<typename Ch>
void CRV_XMLCommon<Ch>::AppendAttribute(rapidxml::xml_node<Ch>* node, const Ch* name, const Ch* value) {
    node->append_attribute(
        _xmlDocument->allocate_attribute(
            name,
            _xmlDocument->allocate_string(value)
        )
    );
}

template<typename Ch>
void CRV_XMLCommon<Ch>::AppendAttribute(rapidxml::xml_node<Ch>* node, const Ch* name, int value) {
    std::string temp = std::to_string(value);
    node->append_attribute(
        _xmlDocument->allocate_attribute(
            name,
            _xmlDocument->allocate_string(temp.c_str())
        )
    );
}

template<typename Ch>
void CRV_XMLCommon<Ch>::AppendAttribute(rapidxml::xml_node<Ch>* node, const Ch* name, uint8_t value) {
    std::string temp = std::to_string(value);
    node->append_attribute(
        _xmlDocument->allocate_attribute(
            name,
            _xmlDocument->allocate_string(temp.c_str())
        )
	);
}

template<typename Ch>
void CRV_XMLCommon<Ch>::AppendAttribute(rapidxml::xml_node<Ch>* node, const Ch* name, uint32_t value) {
    std::string temp = std::to_string(value);

    node->append_attribute(
        _xmlDocument->allocate_attribute(
            name,
            _xmlDocument->allocate_string(temp.c_str())
        )
    );
}

template<typename Ch>
void CRV_XMLCommon<Ch>::AppendAttribute(rapidxml::xml_node<Ch>* node, const Ch* name, float value) {
    std::string temp = std::to_string(value);

    node->append_attribute(
        _xmlDocument->allocate_attribute(
            name,
            _xmlDocument->allocate_string(temp.c_str())
        )
    );
}

template<typename Ch>
CRV_XMLCommon<Ch>::CRV_XMLCommon()
    : _xmlDocument(std::make_unique<rapidxml::xml_document<Ch>>()) {

}