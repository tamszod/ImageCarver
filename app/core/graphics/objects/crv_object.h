#pragma once

#include "utils/type.h"
#include "core/graphics/render/crv_canvas.h"

#include <string>
#include <memory>

namespace crv::graphics {

	class LineObject;
	class RectangleObject;
	class OvalObject;

	class Object {
	public:
		[[nodiscard]] static std::unique_ptr<crv::graphics::Object> Create(const std::string &typeName);

		//* UI event handling *//

		// Enumeration for the resize handle of the object.
		enum class ResizePoint {
			NONE = 0,
			TOP,
			TOP_LEFT,
			TOP_RIGHT,
			LEFT,
			RIGHT,
			BOTTOM,
			BOTTOM_LEFT,
			BOTTOM_RIGHT
		};

		// Move object bounding box
		virtual bool OnMove(PointF offset);

		// Resize object bounding box
		virtual bool OnResize(ResizePoint resizeStart, PointF offset);

		// Rotate object bounding box
		virtual bool OnRotate(float rotateBy);

		//** Paint event **//

		virtual void OnDraw(CRV_Canvas &canvas) = 0;

		//** Properties **//

		// Bounding box
		virtual const BoundingBoxF& GetBBox() const;
		virtual void SetBBox(const BoundingBoxF &boundingBox);
		float GetWidth() const;
		float GetHeight() const;

		// Rotation
		float GetRotation() const;
		void SetRotation(float rotationDegree);

		// Generic color
		virtual bool SupportsColor() const;
		virtual const std::shared_ptr<CRV_Color> GetColor() const;
		virtual void SetColor(std::unique_ptr<CRV_Color> color);

		// Fill color
		virtual bool SupportsFillColor() const;
		virtual const std::shared_ptr<CRV_Color> GetFillColor() const;
		virtual void SetFillColor(std::unique_ptr<CRV_Color> color);

		// Line width
		virtual bool SupportsLineWidth() const;
		virtual int GetLineWidth() const;
		virtual void SetLineWidth(int width);

		// ID in projects object array.
		uint32_t GetObjNum() const;
		void SetOjbNum(uint32_t objNum);

		//** RTTI interfaces **//

		virtual bool IsLine() const;
		virtual bool IsOval() const;
		virtual bool IsRectangle() const;
		virtual bool IsCommonFigure() const;
		virtual bool IsCommonLine() const;

		virtual const LineObject *AsLine() const;
		virtual const RectangleObject *AsRectangle() const;
		virtual const OvalObject *AsOval() const;

		virtual LineObject *AsMutableLine();
		virtual RectangleObject *AsMutableRectangle();
		virtual OvalObject *AsMutableOval();

		// Object raw name
		virtual const char* GetTypeName() const = 0;

		virtual ~Object() = default;
	protected:
		explicit Object() = default;

		BoundingBoxF boundingBox_{};
		float rotationDegree_ = 0.f;

	private:
		uint32_t objNum_ = 0;
	};

}