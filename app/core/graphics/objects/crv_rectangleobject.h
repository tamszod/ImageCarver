#pragma once

#include "crv_commonfigureobject.h"

namespace crv::graphics {
	class RectangleObject : public CommonFigureObject {
	public:
		void OnDraw(CRV_Canvas &canvas) override;

		const char* GetTypeName() const override;

		bool IsRectangle() const override;
		const crv::graphics::RectangleObject *AsRectangle() const override;
		crv::graphics::RectangleObject *AsMutableRectangle() override;

		RectangleObject() = default;
		~RectangleObject() override = default;
	};
}