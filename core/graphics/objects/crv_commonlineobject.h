#pragma once

#include "crv_object.h"

namespace crv {
	namespace graphics {
		class CommonLineObject : public Object {
		public:
			virtual bool SupportsColor() const override;
			virtual const std::shared_ptr<CRV_Color> GetColor() const override;
			virtual void SetColor(std::unique_ptr<CRV_Color> color) override;
			virtual bool SupportsLineWidth() const override;
			virtual int GetLineWidth() const override;
			virtual void SetLineWidth(int width) override;

			bool IsCommonLine() const override;

			CommonLineObject() = default;
			~CommonLineObject() = default;
		private:
			int _width = 1;
			std::shared_ptr<CRV_Color> _color = CRV_Color::Create(0, 0, 0);
		};
	}
}