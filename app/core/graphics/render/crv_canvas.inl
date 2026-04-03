
template<CommonImageType T>
std::unique_ptr<T> CRV_Canvas::DetachImage() {
    auto raw = _target.release();
    if (auto casted = dynamic_cast<T*>(raw)) {
        return std::unique_ptr<T>(casted);
    }
    delete raw;
    return nullptr;
}