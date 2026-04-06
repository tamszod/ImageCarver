#pragma once

#include "utils/types/crv_concept.h"

namespace crv::type {
    template<CommonNumericType T = int>
    struct Point {
        T x = 0;
        T y = 0;

        Point() = default;
        Point(T x, T y) : x(x), y(y) {}
    };
}

using CRV_Point  = crv::type::Point<int>;
using CRV_PointF = crv::type::Point<float>;