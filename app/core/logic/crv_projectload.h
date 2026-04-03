#pragma once

#include "crv_project.h"
#include "../../utils/types/bytes.h"
#include "../../utils/types/crv_xmlcommon.h"

#include "../../../ext/RapidXML/rapidxml.hpp"

class CRV_ProjectLoad : CRV_XMLCommon<char> {
public:
	CRV_ProjectLoad(crv::type::ByteStream& stream);
	std::unique_ptr<CRV_Project> Load();
protected:
	crv::type::ByteStream& _stream;
	std::unique_ptr<CRV_Project> _project{};
	
	void _ParseHeader(rapidxml::xml_node<char>* headerNode);
	void _ParseView(rapidxml::xml_node<char>* viewNode);
	void _ParseGraphicObjects(rapidxml::xml_node<char>* annotationsNode);

	std::unique_ptr<crv::graphics::Object> _ParseGraphicObject(rapidxml::xml_node<char>* node);
};