#include "crv_projectload.h"
#include "core/graphics/objects/crv_object.h"
#include "core/graphics/objects/crv_lineobject.h"
#include "utils/constants/crv_xmltag.h"

CRV_ProjectLoad::CRV_ProjectLoad(crv::type::ByteStream&& stream)
    : CRV_XMLCommon()
    , _stream(stream) {
};

std::unique_ptr<CRV_Project> CRV_ProjectLoad::Load() {
    if (_stream.empty()) {
        return nullptr;
    }

    if (_stream.back() != '\0'){
        _stream.push_back('\0');
    }

    Parse(reinterpret_cast<char*>(_stream.data()));

    auto* root = FindRootNodeElement(crv::xmltag::PROJECT);

    if (!root) {
        return nullptr;
    }

    _project = CRV_Project::Create();

    if (!_project) {
		return nullptr;
    }

    // Parse header tag
    if (auto* header = FindNodeElement(root, crv::xmltag::HEADER)) {
        ParseHeader(header);
    }

    // Parse view tag
    if (auto* view = FindNodeElement(root, crv::xmltag::VIEW)) {
        ParseView(view);
    }

    // Parse graphical objects
    if (auto* graphicalObjects = FindNodeElement(root, crv::xmltag::GRAPHICAL_OBJECTS)) {
        ParseGraphicalObjects(graphicalObjects);
    }

    return std::move(_project);
}

void CRV_ProjectLoad::ParseHeader(rapidxml::xml_node<char>* headerNode) {
    if (auto creation = FindNodeElementValue(headerNode, crv::xmltag::CREATION_DATE)) {
        _project->SetCreationDate(*creation);
    }
    if (auto modification = FindNodeElementValue(headerNode, crv::xmltag::MODIFICATION_DATE)) {
        _project->SetModificationDate(*modification);
    }
}

void CRV_ProjectLoad::ParseView(rapidxml::xml_node<char>* viewNode) {
    if (auto* size = FindNodeElement(viewNode, crv::xmltag::SIZE)) {
        if (auto width = FindAttributeIntValue(viewNode, crv::xmltag::WIDTH)) {
            _project->SetWidth(*width);
        }
        if (auto height = FindAttributeIntValue(viewNode, crv::xmltag::HEIGHT)) {
            _project->SetHeight(*height);
        }
    }
}

void CRV_ProjectLoad::ParseGraphicalObjects(rapidxml::xml_node<char>* graphicalObjectsNode) {
    for (auto* graphicalObjectNode = graphicalObjectsNode->first_node(); graphicalObjectNode; graphicalObjectNode = graphicalObjectNode->next_sibling()) {
        auto graphicalObject = ParseGraphicalObject(graphicalObjectNode);
        if (graphicalObject) {
            _project->AddGraphicalObject(std::move(graphicalObject));
        }
    }
}

std::unique_ptr<crv::graphics::Object> CRV_ProjectLoad::ParseGraphicalObject(rapidxml::xml_node<char>* node) {
    // <graphical_object id="1">
	std::unique_ptr<crv::graphics::Object> graphicalObject = crv::graphics::Object::Create(node->name());

    if (!graphicalObject) {
        return nullptr;
	}

    if (auto objNum = FindAttributeUINT32TValue(node, crv::xmltag::ID)) {
        graphicalObject->SetOjbNum(*objNum);
    }

    // <bbox .../> or <points .../>
    if (graphicalObject->IsLine()) {
        if (auto line = graphicalObject->AsMutableLine()) {
            if (auto points = FindNodeElementPointFListValue(node, crv::xmltag::POINTS, crv::xmltag::POINT)) {
                for (size_t i = 0; i < (*points).size(); ++i) {
                    line->SetPoint(0, (*points)[i]);
                }
            }
        }
    }
    else {
		if (auto bbox = FindNodeElementBoundingBoxFValue(node, crv::xmltag::BBOX)) {
            graphicalObject->SetBBox(*bbox);
        }
    }

    //// <color .../>
    if (graphicalObject->SupportsColor()) {
        if (auto color = FindNodeElementCRVColorValue(node, crv::xmltag::COLOR)) {
            graphicalObject->SetColor(std::move(*color));
		}
    }

    //// <fill_color .../>
    if (graphicalObject->SupportsFillColor()) {
		if (auto fillColor = FindNodeElementCRVColorValue(node, crv::xmltag::FILL_COLOR)) {
            graphicalObject->SetFillColor(std::move(*fillColor));
        }
    }

    //// <line_width .../>
    if (graphicalObject->SupportsLineWidth()) {
        if (auto lineWidth = FindNodeElementIntValue(node, crv::xmltag::LINE_WIDTH)) {
            graphicalObject->SetLineWidth(*lineWidth);
        }
    }

    return graphicalObject;
}