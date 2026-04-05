#pragma once

#include "crv_project.h"
#include "utils/types/bytes.h"
#include "utils/types/crv_xmlcommon.h"

class CRV_ProjectLoad : CRV_XMLCommon<char> {
public:
	explicit CRV_ProjectLoad(crv::type::ByteStream& stream);
	std::unique_ptr<CRV_Project> Load();
protected:
	void ParseHeader(rapidxml::xml_node<char>* headerNode);
	void ParseView(rapidxml::xml_node<char>* viewNode);
	void ParseGraphicalObjects(rapidxml::xml_node<char>* graphicalObjectsNode);

	std::unique_ptr<crv::graphics::Object> ParseGraphicalObject(rapidxml::xml_node<char>* node);

    crv::type::ByteStream& _stream;
    std::unique_ptr<CRV_Project> _project{};
};