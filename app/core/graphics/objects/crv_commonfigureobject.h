#pragma once

#include "crv_commonlineobject.h"

namespace crv {
	namespace graphics {
		class CommonFigureObject : public CommonLineObject {
		public:
			virtual bool SupportsFillColor() const override;
			virtual const std::shared_ptr<CRV_Color> GetFillColor() const override;
			virtual void SetFillColor(std::unique_ptr<CRV_Color> color) override;

			bool IsCommonFigure() const override;

			CommonFigureObject() = default;
			~CommonFigureObject() = default;
		private:
			std::shared_ptr<CRV_Color> _fillColor{};
		};
	}
}