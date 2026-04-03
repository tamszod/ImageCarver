#pragma once

namespace crv {
	namespace type {
		struct Point {
			int x = 0;
			int y = 0;
			Point(int x, int y) : x(x), y(y) {}
			Point() = default;
		};

		struct PointF {
			float x = 0.f;
			float y = 0.f;

			PointF() = default;
			PointF(float x, float y) : x(x), y(y) {}
		};

		struct BoundingBoxF {
			float left = 0.f;
			float top = 0.f;
			float right = 0.f;
			float bottom = 0.f;

			BoundingBoxF() = default;
			BoundingBoxF(float left, float top, float right, float bottom) : left(left), top(top), right(right), bottom(bottom) {}
			BoundingBoxF& operator+=(const PointF& delta);
		};

		struct Matrix6F {
			float a = 1.f;
			float b = 0.f;
			float c = 0.f;
			float d = 1.f;
			float e = 0.f;
			float f = 0.f;

			Matrix6F() = default;
		};

		struct Rectangle {
			int left = 0;
			int top = 0;
			int right = 0;
			int bottom = 0;

			Rectangle() = default;
			Rectangle(int left, int top, int right, int bottom) : left(left), top(top), right(right), bottom(bottom) {}
		};
	}
}

using crv::type::Point;
using crv::type::PointF;
using crv::type::BoundingBoxF;
using crv::type::Matrix6F;