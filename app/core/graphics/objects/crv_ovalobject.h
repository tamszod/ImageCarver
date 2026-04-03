#pragma once

#include "crv_commonfigureobject.h"

namespace crv {
	namespace graphics {
		class OvalObject : public CommonFigureObject {
		public:
			virtual void OnDraw(CRV_Canvas& canvas) override;

			virtual const char* GetTypeName() const override;

			bool IsOval() const override;
			const crv::graphics::OvalObject* AsOval() const override;
			crv::graphics::OvalObject* AsMutableOval() override;

			OvalObject() = default;
			~OvalObject() = default;
		};
	}
}