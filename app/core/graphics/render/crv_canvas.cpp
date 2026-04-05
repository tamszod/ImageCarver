#include "crv_canvas.h"
#include "utils/types/crv_color.h"

#include <cmath>

std::unique_ptr<crv::graphics::CommonImage> CRV_Canvas::AttachImage(std::unique_ptr<crv::graphics::CommonImage> obj) {
	auto oldObj = std::move(target_);
	target_ = std::move(obj);
	return oldObj;
}

std::unique_ptr<CRV_Pen> CRV_Canvas::SelectPen(std::unique_ptr<CRV_Pen> pen) {
	auto oldPen = std::move(pen_);
	pen_ = std::move(pen);
	return oldPen;
}

std::unique_ptr<CRV_Brush> CRV_Canvas::SelectBrush(std::unique_ptr<CRV_Brush> brush) {
	auto oldBrush = std::move(brush_);
	brush_ = std::move(brush);
	return oldBrush;
}

CRV_Canvas::CRV_Canvas(
	std::unique_ptr<crv::graphics::CommonImage> target,
	std::unique_ptr<CRV_Pen> pen,
	std::unique_ptr<CRV_Brush> brush) 
	: target_(std::move(target))
	, pen_(std::move(pen))
	, brush_(std::move(brush))
	, fallbackColor_()
	, fallbackBackgroundColor_ () {

}

void CRV_Canvas::MoveTo(int x, int y) {
	_currentPosition = { static_cast<float>(x), static_cast<float>(y) };
}

void CRV_Canvas::MoveTo(float x, float y) {
	_currentPosition = { x, y };
}

void CRV_Canvas::DrawLineTo(int x, int y) {
	if (target_) {
		target_->AddLine(static_cast<int>(std::round(_currentPosition.x)), static_cast<int>(std::round(_currentPosition.y)), x, y, GetSelectedColor(), GetSelectedWidth());
	}
	MoveTo(x, y);
}

void CRV_Canvas::DrawLineTo(float x, float y) {
	if (target_) {
		target_->AddLine(_currentPosition.x, _currentPosition.y, x, y, GetSelectedColor(), GetSelectedWidth<float>());
	}
	MoveTo(x, y);
}

void CRV_Canvas::DrawRectangle(const crv::type::Rectangle& rect) {
	if (target_) {
		target_->AddRectangle(rect, GetSelectedColor(), GetSelectedWidth(), GetSelectedBackgroundColor());
	}
}

void CRV_Canvas::DrawRectangle(const BoundingBoxF& rect) {
	if (target_) {
		target_->AddRectangle(rect, GetSelectedColor(), GetSelectedWidth<float>(), GetSelectedBackgroundColor());
	}
}

void CRV_Canvas::FillRectangle(const crv::type::Rectangle& rect) {
	if (target_) {
		target_->FillRectangle(rect, GetSelectedColor());
	}
}

void CRV_Canvas::FillRectangle(const BoundingBoxF& rect) {
	if (target_) {
		target_->FillRectangle(rect, GetSelectedColor());
	}
}

void CRV_Canvas::DrawOval(const crv::type::Rectangle& rect) {
	if (target_) {
		target_->AddOval(rect, GetSelectedColor(), GetSelectedWidth(), GetSelectedBackgroundColor());
	}
}

void CRV_Canvas::DrawOval(const BoundingBoxF& rect) {
	if (target_) {
		target_->AddOval(rect, GetSelectedColor(), GetSelectedWidth<float>(), GetSelectedBackgroundColor());
	}
}

void CRV_Canvas::FillOval(const crv::type::Rectangle& rect) {
	if (target_) {
		target_->FillOval(rect, GetSelectedBackgroundColor());
	}
}

void CRV_Canvas::FillOval(const BoundingBoxF& rect) {
	if (target_) {
		target_->FillOval(rect, GetSelectedBackgroundColor());
	}
}

const CRV_Color& CRV_Canvas::GetSelectedColor() {
	if (pen_){
		return pen_->GetColor();
	}
	if (!fallbackColor_){
		fallbackColor_ = CRV_Color::Create(0,0,0,255);
	}
	return *fallbackBackgroundColor_;
}

const CRV_Color& CRV_Canvas::GetSelectedBackgroundColor() {
	if (brush_){
		return brush_->GetColor();
	}
	if (!fallbackBackgroundColor_){
		fallbackBackgroundColor_ = CRV_Color::Create(255,255,255, 255);
	}
	return *fallbackBackgroundColor_;
}