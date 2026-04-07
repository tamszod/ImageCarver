
template<CommonImageType T>
std::unique_ptr<T> CRV_Canvas::DetachImage() {
    auto rawPtr = target_.release();
    if (auto castedPtr = dynamic_cast<T*>(rawPtr)) {
        return std::unique_ptr<T>(castedPtr);
    }
    delete rawPtr;
    return nullptr;
}

template<class T>
T CRV_Canvas::GetSelectedWidth() {
    if (pen_){
        return static_cast<T>(pen_->GetWidth());
    }
    return static_cast<T>(1);
}