#pragma once

#include "crv_brush.h"

std::unique_ptr<CRV_Brush> CRV_Brush::Create(std::unique_ptr<CRV_Color> color) {
	return std::unique_ptr<CRV_Brush>(new CRV_Brush(std::move(color)));
}

std::unique_ptr<CRV_Brush> CRV_Brush::Create(const std::shared_ptr<CRV_Color>& color) {
	return std::unique_ptr<CRV_Brush>(new CRV_Brush(color));
}

CRV_Brush::CRV_Brush(std::unique_ptr<CRV_Color> color) 
	: CRV_PaintTool(std::move(color)) {
}

CRV_Brush::CRV_Brush(const std::shared_ptr<CRV_Color>& color) 
	: CRV_PaintTool(color) {

}