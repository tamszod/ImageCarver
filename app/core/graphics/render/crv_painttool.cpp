#include "crv_painttool.h"


const CRV_Color& CRV_PaintTool::_GetDefaultColor() const {
	if (!gDefaultColor) {
		gDefaultColor = CRV_Color::Create();
	}
	return *gDefaultColor;
}

std::unique_ptr<CRV_Color> CRV_PaintTool::gDefaultColor = nullptr;
