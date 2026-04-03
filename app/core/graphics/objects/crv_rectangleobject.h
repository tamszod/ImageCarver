#pragma once

#include "crv_commonfigureobject.h"

namespace crv {
	namespace graphics {
		class RectangleObject : public CommonFigureObject {
		public:
			virtual void OnDraw(CRV_Canvas& canvas) override;

			virtual const char* GetTypeName() const override;

			bool IsRectangle() const override;
			const crv::graphics::RectangleObject* AsRectangle() const override;
			crv::graphics::RectangleObject* AsMutableRectangle() override;

			RectangleObject() = default;
			~RectangleObject() = default;
		};
	}
}