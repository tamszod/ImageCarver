#pragma once

#include "crv_commonlineobject.h"

namespace crv::graphics {
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

        void OnDraw(CRV_Canvas &canvas) override;

        void SetBBox(const BoundingBoxF &boundingBox) override;
        virtual void UpdateBBox();

        virtual const PointF& GetStartPoint() const;
        virtual void SetStartPoint(const PointF &point);
        virtual const PointF& GetEndPoint() const;
        virtual void SetEndPoint(const PointF &point);
        virtual LineHeadType GetStartLineHead() const;
        virtual void SetStartLineHead(LineHeadType type);
        virtual LineHeadType GetEndLineHead() const;
        virtual void SetEndLineHead(LineHeadType type);
        virtual size_t GetPointCount() const;
        virtual const PointF& GetPoint(size_t index) const;
        virtual void SetPoint(size_t index, const PointF &point);

        const char* GetTypeName() const override;

        bool IsLine() const override;
        const LineObject *AsLine() const override;
        LineObject *AsMutableLine() override;

        explicit LineObject() = default;
        ~LineObject() override = default;

    private:
        PointF startPoint_{};
        PointF endPoint_{};
        LineHeadType startLineHead_ = LineHeadType::NONE;
        LineHeadType endLineHead_ = LineHeadType::NONE;
    };
}
