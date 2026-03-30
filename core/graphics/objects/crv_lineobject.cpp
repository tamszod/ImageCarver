#pragma once

#include "crv_lineobject.h"

#include "../render/crv_canvas.h"
#include "../render/crv_pen.h"

void crv::graphics::LineObject::OnDraw(CRV_Canvas& canvas) {
	auto pen = CRV_Pen::Create(GetColor(), GetLineWidth());
	auto previousPen = canvas.SelectPen(std::move(pen));
	canvas.MoveTo(_startPoint.x, _startPoint.y);
	canvas.DrawLineTo(_endPoint.x, _endPoint.y);
	canvas.SelectPen(std::move(previousPen));
}

void crv::graphics::LineObject::SetBBox(const BoundingBoxF& boundingBox) {

}

void crv::graphics::LineObject::UpdateBBox() {
	crv::graphics::Object::SetBBox( BoundingBoxF{
		std::min(_startPoint.x, _endPoint.x),
		std::min(_startPoint.y, _endPoint.y),
		std::max(_startPoint.x, _endPoint.x),
		std::max(_startPoint.y, _endPoint.y)
	});
}

PointF crv::graphics::LineObject::GetStartPoint() const {
	return _startPoint; 
}

void crv::graphics::LineObject::SetStartPoint(const PointF& point) {
	_startPoint = point; 
	UpdateBBox();
}

PointF crv::graphics::LineObject::GetEndPoint() const {
	return _endPoint; 
}

void crv::graphics::LineObject::SetEndPoint(const PointF& point) {
	_endPoint = point;
	UpdateBBox();
}

crv::graphics::LineObject::LineHeadType crv::graphics::LineObject::GetStartLineHead() const {
	return _startLineHead;
}

void crv::graphics::LineObject::SetStartLineHead(crv::graphics::LineObject::LineHeadType type) {
	_startLineHead = type;
}

crv::graphics::LineObject::LineHeadType crv::graphics::LineObject::GetEndLineHead() const {
	return _endLineHead;
}

void crv::graphics::LineObject::SetEndLineHead(crv::graphics::LineObject::LineHeadType type) {
	_endLineHead = type;
}

size_t crv::graphics::LineObject::GetPointCount() const {
	return 2;
}

const PointF crv::graphics::LineObject::GetPoint(size_t index) const {
	if (index == 0) {
		return _startPoint;
	}
	else if (index == 1) {
		return _endPoint;
	}
	return {};
}

void crv::graphics::LineObject::SetPoint(size_t index, const PointF& point) {
	if (index == 0) {
		_startPoint = point;
	}
	else if (index == 1) {
		_endPoint = point;
	}
}

const char* crv::graphics::LineObject::GetTypeName() const {
	return "line";
}

bool crv::graphics::LineObject::IsLine() const {
	return true;
}

const crv::graphics::LineObject* crv::graphics::LineObject::AsLine() const {
	return this;
}

crv::graphics::LineObject* crv::graphics::LineObject::AsMutableLine() {
	return this;
}