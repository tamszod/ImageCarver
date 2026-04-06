template<CommonNumericType T>
crv::type::Rectangle<T>& crv::type::Rectangle<T>::operator+=(const crv::type::Point<T>& delta) {
    left += delta.x;
    right += delta.x;
    top += delta.y;
    bottom += delta.y;
    return *this;
}