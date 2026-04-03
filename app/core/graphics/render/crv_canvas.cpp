#pragma once

#include "crv_canvas.h"
#include "../../../utils/types/crv_color.h"

#include <cmath>

std::unique_ptr<crv::graphics::CommonImage> CRV_Canvas::AttachImage(std::unique_ptr<crv::graphics::CommonImage> obj) {
	auto oldObj = std::move(_target);
	_target = std::move(obj);
	return oldObj;
}

std::unique_ptr<CRV_Pen> CRV_Canvas::SelectPen(std::unique_ptr<CRV_Pen> pen) {
	auto oldPen = std::move(_pen);
	_pen = std::move(pen);
	//if (!_pen) { // Never allow nullptr pen, default to the default pen
	//	_pen = CRV_Pen::CreatePen();
	//}
	return oldPen;
}

std::unique_ptr<CRV_Brush> CRV_Canvas::SelectBrush(std::unique_ptr<CRV_Brush> brush) {
	auto oldBrush = std::move(_brush);
	_brush = std::move(brush);
	//if (!_brush) { // Never allow nullptr brush, default to the default brush
	//	_brush = std::make_unique<CRV_Brush>();
	//}
	return oldBrush;
}

CRV_Canvas::CRV_Canvas(
	std::unique_ptr<crv::graphics::CommonImage> target,
	std::unique_ptr<CRV_Pen> pen,
	std::unique_ptr<CRV_Brush> brush) 
	: _target(std::move(target))
	, _pen(std::move(pen))
	, _brush( std::move(brush)) {

}

void CRV_Canvas::MoveTo(int x, int y) {
	_currentPosition = { static_cast<float>(x), static_cast<float>(y) };
}

void CRV_Canvas::MoveTo(float x, float y) {
	_currentPosition = { x, y };
}

void CRV_Canvas::DrawLineTo(int x, int y) {
	if (_target) {
		_target->AddLine(std::lround(_currentPosition.x), std::lround(_currentPosition.y), x, y, _pen->GetColor(), _pen->GetWidth());
	}
	MoveTo(x, y);
}

void CRV_Canvas::DrawLineTo(float x, float y) {
	if (_target) {
		_target->AddLine(_currentPosition.x, _currentPosition.y, x, y, _pen->GetColor(), static_cast<float>(_pen->GetWidth()));
	}
	MoveTo(x, y);
}

void CRV_Canvas::DrawRectangle(const crv::type::Rectangle& rect) {
	if (_target) {
		_target->AddRectangle(rect, _pen->GetColor(), _pen->GetWidth(), _brush->GetColor());
	}
}

void CRV_Canvas::DrawRectangle(const BoundingBoxF& rect) {
	if (_target) {
		_target->AddRectangle(rect, _pen->GetColor(), static_cast<float>(_pen->GetWidth()), _brush->GetColor());
	}
}

void CRV_Canvas::FillRectangle(const crv::type::Rectangle& rect) {
	if (_target) {
		_target->FillRectangle(rect, _brush->GetColor());
	}
}

void CRV_Canvas::FillRectangle(const BoundingBoxF& rect) {
	if (_target) {
		_target->FillRectangle(rect, _brush->GetColor());
	}
}

void CRV_Canvas::DrawOval(const crv::type::Rectangle& rect) {
	if (_target) {
		_target->AddOval(rect, _pen->GetColor(), _pen->GetWidth(), _brush->GetColor());
	}
}

void CRV_Canvas::DrawOval(const BoundingBoxF& rect) {
	if (_target) {
		_target->AddOval(rect, _pen->GetColor(), static_cast<float>(_pen->GetWidth()), _brush->GetColor());
	}
}

void CRV_Canvas::FillOval(const crv::type::Rectangle& rect) {
	if (_target) {
		_target->FillOval(rect, _brush->GetColor());
	}
}

void CRV_Canvas::FillOval(const BoundingBoxF& rect) {
	if (_target) {
		_target->FillOval(rect, _brush->GetColor());
	}
}