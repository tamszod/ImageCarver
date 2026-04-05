#include "crv_lineobject.h"
#include "core/graphics/render/crv_canvas.h"
#include "core/graphics/render/crv_pen.h"

void crv::graphics::LineObject::OnDraw(CRV_Canvas& canvas) {
	auto pen = CRV_Pen::Create(GetColor(), GetLineWidth());
	auto previousPen = canvas.SelectPen(std::move(pen));
	canvas.MoveTo(startPoint_.x, startPoint_.y);
	canvas.DrawLineTo(endPoint_.x, endPoint_.y);
	canvas.SelectPen(std::move(previousPen));
}

void crv::graphics::LineObject::SetBBox(const BoundingBoxF& boundingBox) {
    std::vector<PointF> transformedPoints{};
	transformedPoints.reserve(GetPointCount());
	auto prevWidth = GetWidth();
	auto prevHeight = GetHeight();
	auto width = boundingBox.right - boundingBox.left;
	auto height = boundingBox.bottom - boundingBox.top;;
	for (size_t i = 0; i < GetPointCount(); ++i) {
		const auto& prevPoint = GetPoint(i);
		SetPoint( i,
				{ // new box side + (prev scale) * new size
						boundingBox_.left+((prevPoint.x-boundingBox_.left)/prevWidth)*width,
						boundingBox_.top+((prevPoint.y-boundingBox_.top)/prevHeight)*height,
				});
	}
	UpdateBBox();
}

void crv::graphics::LineObject::UpdateBBox() {
	crv::graphics::Object::SetBBox( {
		std::min(startPoint_.x, endPoint_.x),
		std::min(startPoint_.y, endPoint_.y),
		std::max(startPoint_.x, endPoint_.x),
		std::max(startPoint_.y, endPoint_.y)
	});
}

const PointF& crv::graphics::LineObject::GetStartPoint() const {
	return startPoint_;
}

void crv::graphics::LineObject::SetStartPoint(const PointF& point) {
	startPoint_ = point;
}

const PointF& crv::graphics::LineObject::GetEndPoint() const {
	return endPoint_;
}

void crv::graphics::LineObject::SetEndPoint(const PointF& point) {
	endPoint_ = point;
	UpdateBBox();
}

crv::graphics::LineObject::LineHeadType crv::graphics::LineObject::GetStartLineHead() const {
	return startLineHead_;
}

void crv::graphics::LineObject::SetStartLineHead(crv::graphics::LineObject::LineHeadType type) {
	startLineHead_ = type;
}

crv::graphics::LineObject::LineHeadType crv::graphics::LineObject::GetEndLineHead() const {
	return endLineHead_;
}

void crv::graphics::LineObject::SetEndLineHead(crv::graphics::LineObject::LineHeadType type) {
	endLineHead_ = type;
}

size_t crv::graphics::LineObject::GetPointCount() const {
	return 2;
}

const PointF& crv::graphics::LineObject::GetPoint(size_t index) const {
	if (index == 0) {
		return startPoint_;
	}
	else if (index == 1) {
		return endPoint_;
	}
	return {};
}

void crv::graphics::LineObject::SetPoint(size_t index, const PointF& point) {
	if (index == 0) {
		startPoint_ = point;
	}
	else if (index == 1) {
		endPoint_ = point;
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