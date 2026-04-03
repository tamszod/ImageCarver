#include "crv_commonfigureobject.h"

bool crv::graphics::CommonFigureObject::SupportsFillColor() const {
	return true;
}

const std::shared_ptr<CRV_Color> crv::graphics::CommonFigureObject::GetFillColor() const {
	return _fillColor;
}

void crv::graphics::CommonFigureObject::SetFillColor(std::unique_ptr<CRV_Color> color) {
	_fillColor = std::move(color);
}

bool crv::graphics::CommonFigureObject::IsCommonFigure() const {
	return true;
}