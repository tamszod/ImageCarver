#include "crv_math.h"

#include <cmath>

void crv::math::NormalizeRotationDegree(float &degree) {
    degree = std::fmod(degree, 360.0f);
    if (degree < 0.0f) {
        degree += 360.0f;
    }
}