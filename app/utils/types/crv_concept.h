#pragma once

#include <type_traits>

template<typename T>
concept CommonNumericType =
    std::is_same_v<T, int> ||
    std::is_same_v<T, float> ||
    std::is_same_v<T, double>;