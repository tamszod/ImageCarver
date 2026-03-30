#pragma once

#include "../../../utilities/type.h"
#include "../render/crv_canvas.h"

#include <string>
#include <memory>



namespace crv {
	namespace graphics {

		class LineObject;
		class RectangleObject;
		class OvalObject;

		class Object {
		public:

			static std::unique_ptr<crv::graphics::Object> Create(const std::string& typeName);

			/* @brief Enumeration for the resize handle of the object.
			 *
			 */
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

			/* @brief Move the object by the given offset.
			 *
			 * @param offset The offset to move the object by. "x" is the horizontal offset, "y" is the vertical offset.
			 *
			 * @return true if the object was successfully moved, false otherwise.
			 */
			virtual bool OnMove(PointF offset);

			/* @brief Resize the object by the given offset.
			 *
			 * @param resizeStart The resize handle that is being dragged.
			 * @param offset The offset to resize the object by. "x" is the horizontal offset, "y" is the vertical offset.
			 *
			 * @return true if the object was successfully resized, false otherwise.
			 */
			virtual bool OnResize(ResizePoint resizeStart, PointF offset);

			/* @brief Rotate the object by the given degree.
			 *
			 * @param rotateBy The degree to rotate the object by. Positive values rotate clockwise, negative values rotate counterclockwise.
			 *
			 * @return true if the object was successfully rotated, false otherwise.
			 */
			virtual bool OnRotate(float rotateBy);

			//virtual bool OnSave() = 0;

			/* @brief Draw the object on the given canvas.
			 *
			 * @param canvas The canvas to draw the object on.
			 *
			 * @return void
			 */
			virtual void OnDraw(CRV_Canvas& canvas) = 0;

			//////////////////
			//* Properties *//
			//////////////////

			virtual const BoundingBoxF& GetBBox() const;
			virtual void SetBBox(const BoundingBoxF& boundingBox);

			/* @brief Determines whether the object supports color property or not.
			 *
			 * @return true if the object supports color property, false otherwise.
			 */
			virtual bool SupportsColor() const;

			/* @brief Retrieves the color of the object.
			 *
			 * @return A shared pointer to the color of the object. If the object does not support color, returns nullptr.
			 */
			virtual const std::shared_ptr<CRV_Color> GetColor() const;
			virtual void SetColor(std::unique_ptr<CRV_Color> color);

			/* @brief Determines whether the annotation supports fill color property or not.
			 *
			 * @return true if the annotation supports fill color property, false otherwise.
			 */
			virtual bool SupportsFillColor() const;

			/* @brief Retrieves the fill color of the annotation.
			 *
			 * @return A shared pointer to the fill color of the annotation. If the annotation does not support fill color, returns nullptr.
			 */
			virtual const std::shared_ptr<CRV_Color> GetFillColor() const;
			virtual void SetFillColor(std::unique_ptr<CRV_Color> color);

			/* @brief Determines whether the annotation supports line width property or not.
			 *
			 * @return true if the annotation supports line width property, false otherwise.
			 */
			virtual bool SupportsLineWidth() const;
			virtual int GetLineWidth() const;
			virtual void SetLineWidth(int width);

			virtual const char* GetTypeName() const = 0;
			uint32_t GetObjNum() const;
			void SetOjbNum(uint32_t objNum);

			virtual bool IsLine() const;
			virtual bool IsOval() const;
			virtual bool IsRectangle() const;
			virtual bool IsCommonFigure() const;
			virtual bool IsCommonLine() const;

			virtual const LineObject* AsLine() const;
			virtual const RectangleObject* AsRectangle() const;
			virtual const OvalObject* AsOval() const;

			virtual LineObject* AsMutableLine();
			virtual RectangleObject* AsMutableRectangle();
			virtual OvalObject* AsMutableOval();

			virtual ~Object() = default;
		protected:
			Object(uint32_t obj_num = 0);

			BoundingBoxF _BBox{};

			float GetRotation() const;
			void SetRotation(float rotationDegree);
		private:
			float _rotationDegree = 0.f;
			uint32_t _obj_num; //std::string _uuid{};
		};
	}
}