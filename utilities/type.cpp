#pragma once

#include "type.h"

BoundingBoxF& BoundingBoxF::operator+=(const PointF& delta) {
	left += delta.x;
	right += delta.x;
	top += delta.y;
	bottom += delta.y;
	return *this;
}