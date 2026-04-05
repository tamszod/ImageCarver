#pragma once

#include "crv_commonlineobject.h"

namespace crv::graphics {
	class CommonFigureObject : public CommonLineObject {
	public:

		bool SupportsFillColor() const override;
		const std::shared_ptr<CRV_Color> GetFillColor() const override;
		void SetFillColor(std::unique_ptr<CRV_Color> color) override;

		bool IsCommonFigure() const override;

	protected:
		explicit CommonFigureObject() = default;
		~CommonFigureObject() override = default;
	private:
		std::shared_ptr<CRV_Color> fillColor_{};
	};
}