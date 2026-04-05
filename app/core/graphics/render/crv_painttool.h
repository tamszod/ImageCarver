#pragma once

#include "../../../utils/types/crv_color.h"

#include <memory>

class CRV_PaintTool {
public:
	const CRV_Color& GetColor() const {
		return *_color; 
	}
protected:
	CRV_PaintTool() = default;
	CRV_PaintTool(std::unique_ptr<CRV_Color> color) 
		: _color(std::move(color)) {}
	CRV_PaintTool(const std::shared_ptr<CRV_Color>& color)
		: _color(color) {
	}
	const std::shared_ptr<CRV_Color> _color{};
};