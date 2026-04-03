#pragma once

#include "crv_projectsave.h"

#include "RapidXML/rapidxml_print.hpp"
#include "../graphics/objects/crv_lineobject.h"
#include "../../utils/helpers/time.h"

CRV_ProjectSave::CRV_ProjectSave(const CRV_Project& project) 
	: CRV_XMLCommon()
    , _project(project) {

}

crv::type::ByteStream CRV_ProjectSave::Save() {
	_xmlDocument->clear();

    // XML declaration
    auto* decl = _xmlDocument->allocate_node(rapidxml::node_type::node_declaration);
    decl->append_attribute(_xmlDocument->allocate_attribute("version", "1.0"));
    decl->append_attribute(_xmlDocument->allocate_attribute("encoding", "UTF-8"));
    _xmlDocument->append_node(decl);

	// Root node
    auto* projectNode = _xmlDocument->allocate_node(rapidxml::node_type::node_element, "project");
    _xmlDocument->append_node(projectNode);

	// Root children
    projectNode->append_node(_CreateHeaderNode());
    projectNode->append_node(_CreateViewNode());
    projectNode->append_node(_CreateAnnotationsNode());

	// Convert XML document to byte stream
    crv::type::ByteStream buffer;
    rapidxml::print(std::back_inserter(buffer), *_xmlDocument);

    return buffer;
}

rapidxml::xml_node<char>* CRV_ProjectSave::_CreateHeaderNode() {
    // <header>
	auto* header = CreateNodeElement("header");
    // <crv version="1.0"/>
	auto* crv = CreateNodeElement("crv");
	AppendAttribute(crv, "version", "1.0");
    header->append_node(crv);

    // <project version="1.0"/>
	auto* project = CreateNodeElement("project");
	AppendAttribute(project, "version", "1.0");
    header->append_node(project);

    // <creation_date>24.02.2026</creation_date>
    auto* creation = CreateNodeElement(
        "creation_date",
        _project.GetCreationDate().c_str()
	);
    header->append_node(creation);

    // <modification_date>29.03.2026</modification_date>
    auto* modification = CreateNodeElement(
        "modification_date",
        crv::helper::GetQuickTime().c_str()
    );
    header->append_node(modification);
    return header;
}

rapidxml::xml_node<char>* CRV_ProjectSave::_CreateViewNode() {
    // <view>
    auto* view = CreateNodeElement("view");

    // <size width="..." height="..."/>
    auto* size = CreateNodeElement("size");
	AppendAttribute(size, "width", _project.GetWidth());
	AppendAttribute(size, "height", _project.GetHeight());

    view->append_node(size);

    return view;
}

rapidxml::xml_node<char>* CRV_ProjectSave::_CreateAnnotationsNode() {
    // <annotations>
	auto* annotations = CreateNodeElement("annotations");

    for (size_t i = 0; i < _project.GetObjectCount(); i++) {
        const auto& annotation = _project.GetObject(i);
        annotations->append_node(_CreateAnnotationNode(annotation));
	}
    return annotations;
}

rapidxml::xml_node<char>* CRV_ProjectSave::_CreateAnnotationNode(const std::shared_ptr<crv::graphics::Object>& annotation) {
    // <annotation id="1">
	auto* annotationNode = CreateNodeElement(annotation->GetTypeName());
	AppendAttribute(annotationNode, "id", annotation->GetObjNum());

	// <bbox .../> or <points .../>
    if (annotation->IsLine()) {
        auto lineCount = annotation->AsLine()->GetPointCount();
        std::vector<PointF> linePoints;
        linePoints.reserve(lineCount);
		for (size_t i = 0; i < lineCount; i++) {
            linePoints.emplace_back(std::move(annotation->AsLine()->GetPoint(i)));
        }
        auto* points = CreateNodeElement("points", "point", linePoints);
        annotationNode->append_node(points);
    }
    else {
        auto* bbox = CreateNodeElement("bbox", annotation->GetBBox());
        annotationNode->append_node(bbox);
    }

    //// <color .../>
    if (annotation->SupportsColor()) {
		auto* color = CreateNodeElement("color", *annotation->GetColor());
        annotationNode->append_node(color);
    }

    //// <fill_color .../>
    if (annotation->SupportsFillColor()) {
        auto* fillColor = CreateNodeElement("fill_color", *annotation->GetFillColor());
        annotationNode->append_node(fillColor);
    }

    //// <line_width .../>
    if (annotation->SupportsLineWidth()) {
		auto* lineWidth = CreateNodeElement("line_width", annotation->GetLineWidth());
        annotationNode->append_node(lineWidth);
    }

	return annotationNode;
}