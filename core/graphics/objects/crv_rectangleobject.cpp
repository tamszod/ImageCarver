#pragma once

#include "crv_rectangleobject.h"

void crv::graphics::RectangleObject::OnDraw(CRV_Canvas& canvas) {
	auto pen = CRV_Pen::Create(GetColor(), GetLineWidth());
	auto previousPen = canvas.SelectPen(std::move(pen));
	auto brush = CRV_Brush::Create(GetFillColor());
	auto previousBrush = canvas.SelectBrush(std::move(brush));
	canvas.DrawRectangle(GetBBox());
	canvas.SelectBrush(std::move(previousBrush));
	canvas.SelectPen(std::move(previousPen));
}

const char* crv::graphics::RectangleObject::GetTypeName() const {
	return "rectangle";
}

bool  crv::graphics::RectangleObject::IsRectangle() const {
	return true;
}

const  crv::graphics::RectangleObject* crv::graphics::RectangleObject::AsRectangle() const {
	return this;
}

crv::graphics::RectangleObject* crv::graphics::RectangleObject::AsMutableRectangle() {
	return this;
}