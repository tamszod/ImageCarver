#pragma once

#include "crv_commonfigureobject.h"

namespace crv::graphics {
	class OvalObject : public CommonFigureObject {
	public:
		void OnDraw(CRV_Canvas &canvas) override;

		const char* GetTypeName() const override;

		bool IsOval() const override;
		const crv::graphics::OvalObject *AsOval() const override;
		crv::graphics::OvalObject *AsMutableOval() override;

		OvalObject() = default;
		~OvalObject() override = default;
	};
}