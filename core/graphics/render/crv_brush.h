#pragma once

#include "crv_painttool.h"

class CRV_Brush : public CRV_PaintTool {
public:
	static std::unique_ptr<CRV_Brush> Create(std::unique_ptr<CRV_Color> color = CRV_Color::Create());
	static std::unique_ptr<CRV_Brush> Create(const std::shared_ptr<CRV_Color>& color);

protected:
	CRV_Brush(std::unique_ptr<CRV_Color> color = nullptr);
	CRV_Brush(const std::shared_ptr<CRV_Color>& color);

};