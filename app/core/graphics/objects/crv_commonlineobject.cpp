#include "crv_commonlineobject.h"

bool crv::graphics::CommonLineObject::SupportsColor() const {
	return true;
}

const std::shared_ptr<CRV_Color> crv::graphics::CommonLineObject::GetColor() const {
	return _color;
}

void crv::graphics::CommonLineObject::SetColor(std::unique_ptr<CRV_Color> color) {
	_color = std::move(color);
}

bool crv::graphics::CommonLineObject::SupportsLineWidth() const {
	return true;
}

int crv::graphics::CommonLineObject::GetLineWidth() const  {
	return _width;
}

void crv::graphics::CommonLineObject::SetLineWidth(int width) {
	if (width < 1) {
		_width = 1;
	}
	else {
		_width = width;
	}
}

bool crv::graphics::CommonLineObject::IsCommonLine() const {
	return true;
}