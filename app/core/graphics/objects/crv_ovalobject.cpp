#include "crv_ovalobject.h"

void crv::graphics::OvalObject::OnDraw(CRV_Canvas& canvas) {
	auto pen = CRV_Pen::Create(GetColor(), GetLineWidth());
	auto previousPen = canvas.SelectPen(std::move(pen));
	auto brush = CRV_Brush::Create(GetFillColor());
	auto previousBrush = canvas.SelectBrush(std::move(brush));
	canvas.DrawOval(GetBBox());
	canvas.SelectBrush(std::move(previousBrush));
	canvas.SelectPen(std::move(previousPen));
}

const char* crv::graphics::OvalObject::GetTypeName() const {
	return "oval";
}

bool crv::graphics::OvalObject::IsOval() const {
	return true;
}

const crv::graphics::OvalObject* crv::graphics::OvalObject::AsOval() const {
	return this;
}

crv::graphics::OvalObject* crv::graphics::OvalObject::AsMutableOval() {
	return this;
}