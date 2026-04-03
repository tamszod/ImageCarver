#include "crv_pen.h"
#include "crv_painttool.h"

std::unique_ptr<CRV_Pen> CRV_Pen::Create(std::unique_ptr<CRV_Color> color, int width ) {
	return (std::unique_ptr<CRV_Pen>(new CRV_Pen(std::move(color), width)));
}

std::unique_ptr<CRV_Pen> CRV_Pen::Create(const std::shared_ptr<CRV_Color>& color, int width) {
	return (std::unique_ptr<CRV_Pen>(new CRV_Pen(color, width)));
}

int CRV_Pen::GetWidth() const {
	if (!this) {
		return 1;
	}
	return _width; 
}

CRV_Pen::CRV_Pen(std::unique_ptr<CRV_Color> color, int width)
	: CRV_PaintTool(std::move(color)) {
	_SetWidth(width);
}

CRV_Pen::CRV_Pen(const std::shared_ptr<CRV_Color>& color, int width) 
	: CRV_PaintTool(color) {
	_SetWidth(width);
}

void CRV_Pen::_SetWidth(int width) {
	if (width < 1) {
		_width = 1;
	}
	else {
		_width = width;
	}
}