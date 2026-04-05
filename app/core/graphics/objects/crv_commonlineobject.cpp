#include "crv_commonlineobject.h"

bool crv::graphics::CommonLineObject::SupportsColor() const {
	return true;
}

const std::shared_ptr<CRV_Color> crv::graphics::CommonLineObject::GetColor() const {
	return color_;
}

void crv::graphics::CommonLineObject::SetColor(std::unique_ptr<CRV_Color> color) {
	color_ = std::move(color);
}

bool crv::graphics::CommonLineObject::SupportsLineWidth() const {
	return true;
}

int crv::graphics::CommonLineObject::GetLineWidth() const  {
	return width_;
}

void crv::graphics::CommonLineObject::SetLineWidth(int width) {
	if (width < 1) {
		width_ = 1;
	}
	else {
		width_ = width;
	}
}

bool crv::graphics::CommonLineObject::IsCommonLine() const {
	return true;
}