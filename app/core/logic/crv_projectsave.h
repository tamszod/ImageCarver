#pragma once

#include "crv_project.h"
#include "../../utils/types/bytes.h"
#include "../../utils/types/crv_xmlcommon.h"

#include "../../../ext/RapidXML/rapidxml.hpp"

class CRV_ProjectSave : CRV_XMLCommon<char> {
public:
	CRV_ProjectSave(const CRV_Project& project);
	crv::type::ByteStream Save();
protected:
	const CRV_Project& _project;

	rapidxml::xml_node<char>* _CreateHeaderNode();
	rapidxml::xml_node<char>* _CreateViewNode();
	rapidxml::xml_node<char>* _CreateAnnotationsNode();
	rapidxml::xml_node<char>* _CreateAnnotationNode(const std::shared_ptr<crv::graphics::Object>& annotation);
};