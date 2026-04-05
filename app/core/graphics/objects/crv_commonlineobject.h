#pragma once

#include "crv_object.h"

namespace crv::graphics {
	class CommonLineObject : public Object {
	public:
		bool SupportsColor() const override;
		const std::shared_ptr<CRV_Color> GetColor() const override;
		void SetColor(std::unique_ptr<CRV_Color> color) override;

		bool SupportsLineWidth() const override;
		int GetLineWidth() const override;
		void SetLineWidth(int width) override;

		bool IsCommonLine() const override;

	protected:
		explicit CommonLineObject() = default;
		~CommonLineObject() override = default;
	private:
		int width_ = 1;
		std::shared_ptr<CRV_Color> color_ = CRV_Color::Create(0, 0, 0);
	};
}
