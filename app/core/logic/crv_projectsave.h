#pragma once

#include "crv_project.h"
#include "utils/types/bytes.h"
#include "utils/types/crv_xmlcommon.h"

class CRV_ProjectSave : CRV_XMLCommon<char> {
public:
	explicit CRV_ProjectSave(const CRV_Project& project);
	crv::type::ByteStream Save();
protected:
	rapidxml::xml_node<char>* CreateHeaderNode();
	rapidxml::xml_node<char>* CreateViewNode();
	rapidxml::xml_node<char>* CreateGraphicalObjectsNode();
	rapidxml::xml_node<char>* CreateGraphicalObjectNode(std::shared_ptr<const crv::graphics::Object>& object);

    const CRV_Project& project_;
};