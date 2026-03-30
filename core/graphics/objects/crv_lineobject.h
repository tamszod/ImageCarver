#pragma once

#include "crv_commonlineobject.h"


namespace crv {
	namespace graphics {
		class LineObject : public CommonLineObject {
		public:
			enum class LineHeadType {
				NONE = 0
				// OPEN,
				// CLOSED,
				// REVERSED_OPEN,
				// DIAMOND,
				// REVERSED_CLOSED,
				// BUTT,
				// SQUARE,
				// SLASH,
				// ROUND
			};

			virtual void OnDraw(CRV_Canvas& canvas) override;

			virtual void SetBBox(const BoundingBoxF& boundingBox) override;

			virtual void UpdateBBox();

			PointF GetStartPoint() const;
			void SetStartPoint(const PointF& point);
			PointF GetEndPoint() const;
			void SetEndPoint(const PointF& point);

			LineHeadType GetStartLineHead() const;
			void SetStartLineHead(LineHeadType type);
			LineHeadType GetEndLineHead() const;
			void SetEndLineHead(LineHeadType type);

			virtual size_t GetPointCount() const;
			virtual const PointF GetPoint(size_t index) const;
			virtual void SetPoint(size_t index, const PointF& point);

			virtual const char* GetTypeName() const override;

			bool IsLine() const override;
			const LineObject* AsLine() const override;
			LineObject* AsMutableLine() override;

			LineObject() = default;
			~LineObject() = default;
		private:
			PointF _startPoint{};
			PointF _endPoint{};
			LineHeadType _startLineHead = LineHeadType::NONE;
			LineHeadType _endLineHead = LineHeadType::NONE;
		};
	}
}