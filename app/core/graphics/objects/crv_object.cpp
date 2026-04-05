#include "crv_object.h"
#include "crv_ovalobject.h"
#include "crv_lineobject.h"
#include "crv_rectangleobject.h"
#include "../../../utils/crv_helper.h"

#include <memory>

std::unique_ptr<crv::graphics::Object> crv::graphics::Object::Create(const std::string& typeName) {
	if (typeName == "line") {
		return std::make_unique<LineObject>();
	}
	else if (typeName == "rectangle") {
		return std::make_unique<RectangleObject>();
	}
	else if (typeName == "oval") {
		return std::make_unique<OvalObject>();
	}
	return nullptr;
}

bool crv::graphics::Object::OnMove(PointF offset) {
    boundingBox_ += offset;
	return true;
}

bool crv::graphics::Object::OnResize(ResizePoint resizeStart, PointF offset) {
	switch (resizeStart) {
		case ResizePoint::BOTTOM:
		case ResizePoint::BOTTOM_LEFT:
		case ResizePoint::BOTTOM_RIGHT:
            boundingBox_.bottom += offset.y;
			break;
		case ResizePoint::TOP:
		case ResizePoint::TOP_LEFT:
		case ResizePoint::TOP_RIGHT:
            boundingBox_.top += offset.y;
            break;
        default:
            break;
	}
	switch (resizeStart) {
		case ResizePoint::LEFT:
		case ResizePoint::TOP_LEFT:
		case ResizePoint::BOTTOM_LEFT:
            boundingBox_.left += offset.x;
			break;
		case ResizePoint::RIGHT:
		case ResizePoint::TOP_RIGHT:
		case ResizePoint::BOTTOM_RIGHT:
            boundingBox_.right += offset.x;
            break;
        default:
            break;
	}
	if (boundingBox_.left > boundingBox_.right) {
		std::swap(boundingBox_.left, boundingBox_.right);
	}
	if (boundingBox_.top > boundingBox_.bottom) {
		std::swap(boundingBox_.top, boundingBox_.bottom);
	}
	return true;
}

bool crv::graphics::Object::OnRotate(float rotateBy) {
	SetRotation(GetRotation() + rotateBy);
	return true;
}

float crv::graphics::Object::GetRotation() const {
	return rotationDegree_;
}

void crv::graphics::Object::SetRotation(float rotationDegree) {
	rotationDegree_ = rotationDegree;
	crv::helper::NormalizeRotationDegree(rotationDegree_);
}

const BoundingBoxF& crv::graphics::Object::GetBBox() const {
	return boundingBox_;
}

void crv::graphics::Object::SetBBox(const BoundingBoxF& boundingBox) {
	boundingBox_ = boundingBox;
}

float crv::graphics::Object::GetWidth() const {
	return boundingBox_.right - boundingBox_.left;
}

float crv::graphics::Object::GetHeight() const {
	return boundingBox_.bottom - boundingBox_.top;
}

bool crv::graphics::Object::SupportsColor() const {
	return false;
}

const std::shared_ptr<CRV_Color> crv::graphics::Object::GetColor() const {
	return nullptr;
}

void crv::graphics::Object::SetColor(std::unique_ptr<CRV_Color> color) {

}

bool crv::graphics::Object::SupportsFillColor() const {
	return false;
}

const std::shared_ptr<CRV_Color> crv::graphics::Object::GetFillColor() const {
	return nullptr;
}

void crv::graphics::Object::SetFillColor(std::unique_ptr<CRV_Color> color) {

}

bool crv::graphics::Object::SupportsLineWidth() const {
	return false;
}

int crv::graphics::Object::GetLineWidth() const {
	return 0;
}

void crv::graphics::Object::SetLineWidth(int width) {

}

uint32_t crv::graphics::Object::GetObjNum() const {
	return objNum_;
}

void crv::graphics::Object::SetOjbNum(uint32_t objNum) {
	objNum_ = objNum;
}

bool crv::graphics::Object::IsLine() const {
	return false;
}

bool crv::graphics::Object::IsRectangle() const {
	return false;
}

bool crv::graphics::Object::IsOval() const {
	return false;
}

bool crv::graphics::Object::IsCommonFigure() const {
	return false;
}

bool crv::graphics::Object::IsCommonLine() const {
	return false;
}

const crv::graphics::LineObject* crv::graphics::Object::AsLine() const {
	return nullptr;
}

const crv::graphics::RectangleObject* crv::graphics::Object::AsRectangle() const {
	return nullptr;
}

const crv::graphics::OvalObject* crv::graphics::Object::AsOval() const {
	return nullptr;
}

crv::graphics::LineObject* crv::graphics::Object::AsMutableLine() {
	return nullptr;
}

crv::graphics::RectangleObject* crv::graphics::Object::AsMutableRectangle() {
	return nullptr;
}

crv::graphics::OvalObject* crv::graphics::Object::AsMutableOval() {
	return nullptr;
}
