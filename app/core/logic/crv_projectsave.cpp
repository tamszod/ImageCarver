#include "RapidXML/rapidxml_print.hpp"
#include "core/graphics/objects/crv_lineobject.h"
#include "utils/helpers/time.h"
#include "utils/constants//crv_xmltag.h"
#include "crv_projectsave.h"
#include "crv_versioninfo.h"

CRV_ProjectSave::CRV_ProjectSave(const CRV_Project& project) 
	: CRV_XMLCommon()
    , project_(project) {
}

crv::type::ByteStream CRV_ProjectSave::Save() {
	_xmlDocument->clear();

    // XML declaration
    auto* decl = _xmlDocument->allocate_node(rapidxml::node_type::node_declaration);
    decl->append_attribute(_xmlDocument->allocate_attribute("version", "1.0"));
    decl->append_attribute(_xmlDocument->allocate_attribute("encoding", "UTF-8"));
    _xmlDocument->append_node(decl);

	// Root project node
    auto* projectNode = CreateNodeElement(crv::xmltag::PROJECT);
    _xmlDocument->append_node(projectNode);

	// Root children
    projectNode->append_node(CreateHeaderNode());
    projectNode->append_node(CreateViewNode());
    projectNode->append_node(CreateGraphicalObjectsNode());

	// Convert XML document to byte stream
    crv::type::ByteStream buffer;
    rapidxml::print(std::back_inserter(buffer), *_xmlDocument);

    return buffer;
}

rapidxml::xml_node<char>* CRV_ProjectSave::CreateHeaderNode() {
    // <header>
	auto* header = CreateNodeElement(crv::xmltag::HEADER);
    // <crv version="1.0"/>
	auto* crv = CreateNodeElement(crv::xmltag::INSTANCE_VERSION);
	AppendAttribute(crv, crv::xmltag::VERSION, crv::versioninfo::INSTANCE);
    header->append_node(crv);

    // <project version="1.0"/>
	auto* project = CreateNodeElement(crv::xmltag::FILE_VERSION);
	AppendAttribute(project, crv::xmltag::VERSION, crv::versioninfo::CRV_FORMAT);
    header->append_node(project);

    // <creation_date>24.02.2026</creation_date>
    auto* creation = CreateNodeElement(
            crv::xmltag::CREATION_DATE,
            project_.GetCreationDate().c_str()
	);
    header->append_node(creation);

    // <modification_date>29.03.2026</modification_date>
    auto* modification = CreateNodeElement(
            crv::xmltag::MODIFICATION_DATE,
        crv::helper::GetQuickTime().c_str()
    );
    header->append_node(modification);
    return header;
}

rapidxml::xml_node<char>* CRV_ProjectSave::CreateViewNode() {
    // <view>
    auto* view = CreateNodeElement(crv::xmltag::VIEW);

    // <size width="..." height="..."/>
    auto* size = CreateNodeElement(crv::xmltag::SIZE);
	AppendAttribute(size, crv::xmltag::WIDTH, project_.GetWidth());
	AppendAttribute(size, crv::xmltag::HEIGHT, project_.GetHeight());

    view->append_node(size);

    return view;
}

rapidxml::xml_node<char>* CRV_ProjectSave::CreateGraphicalObjectsNode() {
    // <graphical_objects>
	auto* graphicalObjects = CreateNodeElement(crv::xmltag::GRAPHICAL_OBJECTS);

    for (size_t i = 0; i < project_.GetObjectCount(); i++) {
        auto graphicalObject = project_.GetObject(i);
        graphicalObjects->append_node(CreateGraphicalObjectNode(graphicalObject));
	}

    return graphicalObjects;
}

rapidxml::xml_node<char>* CRV_ProjectSave::CreateGraphicalObjectNode(std::shared_ptr<const crv::graphics::Object>& object) {
    // <graphical_object id="1">
	auto* graphicalObjectNode = CreateNodeElement(object->GetTypeName());
	AppendAttribute(graphicalObjectNode, crv::xmltag::ID, object->GetObjNum());

	// <bbox .../> or <points .../>
    if (object->IsLine()) {
        auto lineCount = object->AsLine()->GetPointCount();
        std::vector<CRV_PointF> linePoints;
        linePoints.reserve(lineCount);
		for (size_t i = 0; i < lineCount; i++) {
            linePoints.emplace_back(object->AsLine()->GetPoint(i));
        }
        auto* points = CreateNodeElement(crv::xmltag::POINTS, crv::xmltag::POINT, linePoints);
        graphicalObjectNode->append_node(points);
    }
    else {
        auto* bbox = CreateNodeElement(crv::xmltag::BBOX, object->GetBBox());
        graphicalObjectNode->append_node(bbox);
    }

    //// <color .../>
    if (object->SupportsColor()) {
		auto* color = CreateNodeElement(crv::xmltag::COLOR, *object->GetColor());
        graphicalObjectNode->append_node(color);
    }

    //// <fill_color .../>
    if (object->SupportsFillColor()) {
        auto* fillColor = CreateNodeElement(crv::xmltag::FILL_COLOR, *object->GetFillColor());
        graphicalObjectNode->append_node(fillColor);
    }

    //// <line_width .../>
    if (object->SupportsLineWidth()) {
		auto* lineWidth = CreateNodeElement(crv::xmltag::LINE_WIDTH, object->GetLineWidth());
        graphicalObjectNode->append_node(lineWidth);
    }

	return graphicalObjectNode;
}