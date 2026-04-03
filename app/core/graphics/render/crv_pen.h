#pragma once

#include "crv_painttool.h"

class CRV_Pen : public CRV_PaintTool {
public:
	static std::unique_ptr<CRV_Pen> Create(std::unique_ptr<CRV_Color> color = nullptr, int width = 1);
	static std::unique_ptr<CRV_Pen> Create(const std::shared_ptr<CRV_Color>& color, int width);

	int GetWidth() const;
protected:
	CRV_Pen(std::unique_ptr<CRV_Color> color = nullptr, int width = 1);
	CRV_Pen(const std::shared_ptr<CRV_Color>& color, int width);

	void _SetWidth(int width);

	int _width = 1;
};