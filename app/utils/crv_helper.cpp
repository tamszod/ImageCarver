#pragma once

#include "crv_helper.h"

void crv::helper::NormalizeRotationDegree(float& degree) {
	while (degree < 0.f) {
		degree += 360.f;
	}
	while (degree >= 360.f) {
		degree -= 360.f;
	}
}