#pragma once

#include "../../ext/RapidXML/rapidxml.hpp"
#include "../type.h"

#include <memory>
#include <optional>

template<typename Ch = char>
class CRV_XMLCommon {
protected:
	///////////////
	//* Reading *//
	///////////////
	void Parse(crv::type::ByteStream& stream);
	rapidxml::xml_node<Ch>* FindRootNodeElement(const Ch* name);
	rapidxml::xml_node<Ch>* FindNodeElement(rapidxml::xml_node<char>* node, const Ch* name);
	std::optional<Ch*> FindNodeElementValue(rapidxml::xml_node<char>* node, const Ch* name);
	std::optional<int> FindNodeElementIntValue(rapidxml::xml_node<char>* node, const Ch* name);
	std::optional<std::vector<PointF>> FindNodeElementPointFListValue(rapidxml::xml_node<char>* node, const Ch* name, const Ch* subname);
	std::optional<BoundingBoxF> FindNodeElementBoundingBoxFValue(rapidxml::xml_node<char>* node, const Ch* name);
	std::optional<std::unique_ptr<CRV_Color>> FindNodeElementCRVColorValue(rapidxml::xml_node<char>* node, const Ch* name);
	std::optional<int> FindAttributeIntValue(rapidxml::xml_node<char>* node, const Ch* name);
	std::optional<float> FindAttributeFloatValue(rapidxml::xml_node<char>* node, const Ch* name);
	std::optional<uint8_t> FindAttributeUINT8TValue(rapidxml::xml_node<char>* node, const Ch* name);
	std::optional<uint32_t> FindAttributeUINT32TValue(rapidxml::xml_node<char>* node, const Ch* name);
	

	///////////////
	//* Writing *//
	///////////////
	rapidxml::xml_node<Ch>* CreateNodeElement(const Ch* name);
	rapidxml::xml_node<Ch>* CreateNodeElement(const Ch* name, const Ch* value);
	rapidxml::xml_node<Ch>* CreateNodeElement(const Ch* name, uint32_t value);
	rapidxml::xml_node<Ch>* CreateNodeElement(const Ch* name, const Ch* subname, std::vector<PointF> points);
	rapidxml::xml_node<Ch>* CreateNodeElement(const Ch* name, const BoundingBoxF& value);
	rapidxml::xml_node<Ch>* CreateNodeElement(const Ch* name, const CRV_Color& value);
	void AppendAttribute(rapidxml::xml_node<Ch>* node, const Ch* name, const Ch* value);
	void AppendAttribute(rapidxml::xml_node<Ch>* node, const Ch* name, int value);
	void AppendAttribute(rapidxml::xml_node<Ch>* node, const Ch* name, uint8_t value);
	void AppendAttribute(rapidxml::xml_node<Ch>* node, const Ch* name, uint32_t value);
	void AppendAttribute(rapidxml::xml_node<Ch>* node, const Ch* name, float value);

	CRV_XMLCommon();

	std::vector<Ch> _chstream{};

	std::unique_ptr<rapidxml::xml_document<Ch>> _xmlDocument{};
};

#include "crv_xmlcommon.inl"