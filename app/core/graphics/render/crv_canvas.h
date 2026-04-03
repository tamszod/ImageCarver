#pragma once

#include "../formats/crv_commonimage.h"
#include "../formats/crv_bitmap.h"
#include "crv_pen.h"
#include "crv_brush.h"
#include "../../../utils/type.h"

#include <memory>

/* @
 */
class CRV_Canvas final {
public:
	// Environment management

	/* @brief Attaches a render target to the canvas. Returns the previously attached render target, if any.
	 *
	 * @param obj The graphical object to attach. Can be nullptr to detach the current object.
	 *
	 * @return The previously attached graphical object, or nullptr if there was none.
	 */
	std::unique_ptr<crv::graphics::CommonImage> AttachImage(std::unique_ptr<crv::graphics::CommonImage> obj);

	/* @brief Detaches the currently attached image object from the canvas and returns it.
	 *
	 * @return The detached image object, or nullptr if there was none attached.
	 */
	template<CommonImageType T = crv::graphics::Bitmap>
	std::unique_ptr<T> DetachImage();

	/* @brief Selects a pen for drawing on the canvas. Returns the previously selected pen.
	 *
	 * @param pen The pen to select. Can be nullptr to deselect the current pen (and the default pen will be used instead).
	 *
	 * @return The previously selected pen, or nullptr if there was none.
	 */
	std::unique_ptr<CRV_Pen> SelectPen(std::unique_ptr<CRV_Pen> pen);

	/* @brief Selects a brush for drawing on the canvas. Returns the previously selected brush.
	 *
	 * @param brush The brush to select. Can be nullptr to deselect the current brush (and the default brush will be used instead).
	 *
	 * @return The previously selected brush, or nullptr if there was none.
	 */
	std::unique_ptr<CRV_Brush> SelectBrush(std::unique_ptr<CRV_Brush> brush);

	CRV_Canvas() = default;

	CRV_Canvas(std::unique_ptr<crv::graphics::CommonImage> target, std::unique_ptr<CRV_Pen> pen = nullptr, std::unique_ptr<CRV_Brush> brush = nullptr);

	~CRV_Canvas() = default;

	// Drawing operations

	/* @brief Moves the current drawing position to the specified coordinates.
	 *
	 * @param x The x-coordinate to move to.
	 * @param y The y-coordinate to move to.
	 */
	void MoveTo(int x, int y);
	void MoveTo(float x, float y);

	/* @brief Draws a line from the current drawing position to the specified coordinates using the currently selected pen.
	 *
	 * @param x The x-coordinate of the end point of the line.
	 * @param y The y-coordinate of the end point of the line.
	 */
	void DrawLineTo(int x, int y);
	void DrawLineTo(float x, float y);

	/* @brief Draws a rectangle defined by the specified coordinates using the currently selected pen and brush.
	 *
	 * @param rect The rectangle to draw, defined by its left, top, right, and bottom coordinates.
	 */
	void DrawRectangle(const crv::type::Rectangle& rect);
	void DrawRectangle(const BoundingBoxF& rect);

	/* @brief Fills a rectangle defined by the specified coordinates using the currently selected brush.
	 *
	 * @param rect The rectangle to fill, defined by its left, top, right, and bottom coordinates.
	 */
	void FillRectangle(const crv::type::Rectangle& rect);
	void FillRectangle(const BoundingBoxF& rect);

	void DrawOval(const crv::type::Rectangle& rect);
	void DrawOval(const BoundingBoxF& rect);

	void FillOval(const crv::type::Rectangle& rect);
	void FillOval(const BoundingBoxF& rect);

private:
	std::unique_ptr<crv::graphics::CommonImage> _target{}; // Can be nullpt when no object is attached
	std::unique_ptr<CRV_Pen> _pen = nullptr;
	std::unique_ptr<CRV_Brush> _brush = nullptr;

	PointF _currentPosition{ 0, 0 };
};

#include "crv_canvas.inl"