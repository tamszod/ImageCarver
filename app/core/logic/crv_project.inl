template<CommonImageType T>
std::unique_ptr<T> CRV_Project::DoPaint(std::unique_ptr<T> commonImage) const {
	if (!commonImage) {
		return nullptr;
	}
	CRV_Canvas canvas{ std::move(commonImage) };
	for (const auto& object : _objects) {
		if (object) {
			object->OnDraw(canvas);
		}
	}
	return canvas.DetachImage<T>();
}