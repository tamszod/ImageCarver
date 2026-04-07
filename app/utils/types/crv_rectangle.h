#pragma once

#include "utils/types/crv_concept.h"
#include "crv_point.h"

namespace crv::type {
    template<CommonNumericType T = int>
    struct Rectangle {
        T left = 0;
        T top = 0;
        T right = 0;
        T bottom = 0;

        Rectangle() = default;
        Rectangle(T left, T top, T right, T bottom) : left(left), top(top), right(right), bottom(bottom) {}
        Rectangle& operator+=(const Point<T>& delta);
    };
}

using CRV_Rectangle  = crv::type::Rectangle<int>;
using CRV_RectangleF = crv::type::Rectangle<float>;

#include "crv_rectangle.inl"