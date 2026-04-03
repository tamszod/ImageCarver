#include "crv_projectload.h"
#include "../graphics/objects/crv_object.h"
#include "../graphics/objects/crv_lineobject.h"

CRV_ProjectLoad::CRV_ProjectLoad(crv::type::ByteStream& stream)
    : CRV_XMLCommon()
    , _stream(stream) {
    Parse(_stream);
};

std::unique_ptr<CRV_Project> CRV_ProjectLoad::Load() {
    auto* root = FindRootNodeElement("project");
    if (!root) {
        return nullptr;
    }

    _project = CRV_Project::Create();

    if (!_project) {
		return nullptr;
    }

    // Parse sections
    if (auto* header = FindNodeElement(root, "header")) {
        _ParseHeader(header);
    }

    if (auto* view = FindNodeElement(root, "view")) {
        _ParseView(view);
    }

    if (auto* annotations = FindNodeElement(root, "annotations")) {
        _ParseGraphicObjects(annotations);
    }

    return std::move(_project);
}

void CRV_ProjectLoad::_ParseHeader(rapidxml::xml_node<char>* headerNode) {
    if (auto creation = FindNodeElementValue(headerNode, "creation_date")) {
        _project->SetCreationDate(*creation);
    }
    if (auto modification = FindNodeElementValue(headerNode, "modification_date")) {
        _project->SetModificationDate(*modification);
    }
}

void CRV_ProjectLoad::_ParseView(rapidxml::xml_node<char>* viewNode) {
    if (auto* size = FindNodeElement(viewNode, "size")) {
        if (auto width = FindAttributeIntValue(viewNode, "width")) {
            _project->SetWidth(*width);
        }
        if (auto height = FindAttributeIntValue(viewNode, "height")) {
            _project->SetHeight(*height);
        }
    }
}

void CRV_ProjectLoad::_ParseGraphicObjects(rapidxml::xml_node<char>* annotationsNode) {
    for (auto* node = annotationsNode->first_node(); node; node = node->next_sibling()) {
        auto annotation = _ParseGraphicObject(node);
        if (annotation) {
            _project->AddGraphicObject(std::move(annotation));
        }
    }
}

std::unique_ptr<crv::graphics::Object> CRV_ProjectLoad::_ParseGraphicObject(rapidxml::xml_node<char>* node) {
    // <annotation id="1">
    std::string type = node->name();

	std::unique_ptr<crv::graphics::Object> gobject = crv::graphics::Object::Create(type.c_str());
    if (!gobject) {
        return nullptr;
	}

    if (auto objNum = FindAttributeUINT32TValue(node, "id")) {
        gobject->SetOjbNum(*objNum);
    }

    // <bbox .../> or <points .../>
    if (gobject->IsLine()) {
        if (auto line = gobject->AsMutableLine()) {
            if (auto points = FindNodeElementPointFListValue(node, "points", "point")) {
                for (size_t i = 0; i < (*points).size(); ++i) {
                    line->SetPoint(0, (*points)[i]);
                }
            }
        }
    }
    else {
		if (auto bbox = FindNodeElementBoundingBoxFValue(node, "bbox")) {
            gobject->SetBBox(*bbox);
        }
    }

    //// <color .../>
    if (gobject->SupportsColor()) {
        if (auto color = FindNodeElementCRVColorValue(node, "color")) {
            gobject->SetColor(std::move(*color));
		}
    }

    //// <fill_color .../>
    if (gobject->SupportsFillColor()) {
		if (auto fillColor = FindNodeElementCRVColorValue(node, "fill_color")) {
            gobject->SetFillColor(std::move(*fillColor));
        }
    }

    //// <line_width .../>
    if (gobject->SupportsLineWidth()) {
        if (auto lineWidth = FindNodeElementIntValue(node, "line_width")) {
            gobject->SetLineWidth(*lineWidth);
        }
    }

    return gobject;
}