#pragma once

#include "utils/types/crv_point.h"
#include "utils/types/crv_rectangle.h"
#include "../../../utils/types/bytes.h"
#include "../../../utils/types/crv_color.h"

namespace crv::graphics {

	class Bitmap;

	class CommonImage {
	public:
		virtual bool IsBitmap() const;
		virtual const Bitmap *AsBitmap() const;
		virtual Bitmap *AsMutableBitmap();

		//** Getters for dimensions and pixel data **//
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		virtual float GetWidthF() const = 0;
		virtual float GetHeightF() const = 0;
		virtual std::unique_ptr<CRV_Color> GetPixelColor(int x, int y) const = 0;
		virtual std::unique_ptr<CRV_Color> GetPixelColor(float x, float y) const = 0;

		//** Low-level drawing operations **//
		virtual bool SetPixel(int x, int y, const CRV_Color &color) = 0;
		virtual bool SetPixel(float x, float y, const CRV_Color &color) = 0;
		virtual void AddLine(int x0, int y0, int x1, int y1, const CRV_Color &color, int width) = 0;
		virtual void AddLine(float x0, float y0, float x1, float y1, const CRV_Color &color, float width) = 0;
		virtual void FillRectangle(const CRV_Rectangle &rect, const CRV_Color &backgroundColor) = 0;
		virtual void FillRectangle(const CRV_RectangleF &rect, const CRV_Color &backgroundColor) = 0;
		virtual void AddRectangle(const CRV_Rectangle &rect, const CRV_Color &color, int width) = 0;
		virtual void AddRectangle(const CRV_RectangleF &rect, const CRV_Color &color, float width) = 0;
		virtual void AddRectangle(const CRV_Rectangle &rect, const CRV_Color &color, int width,
								  const CRV_Color &backgroundColor) = 0;
		virtual void AddRectangle(const CRV_RectangleF &rect, const CRV_Color &color, float width,
								  const CRV_Color &backgroundColor) = 0;
		virtual void FillOval(const CRV_Rectangle &rect, const CRV_Color &backgroundColor) = 0;
		virtual void FillOval(const CRV_RectangleF &rect, const CRV_Color &backgroundColor) = 0;
		virtual void AddOval(const CRV_Rectangle &rect, const CRV_Color &color, int width) = 0;
		virtual void AddOval(const CRV_RectangleF &rect, const CRV_Color &color, float width) = 0;
		virtual void AddOval(const CRV_Rectangle &rect, const CRV_Color &color, int width,
							 const CRV_Color &backgroundColor) = 0;
		virtual void AddOval(const CRV_RectangleF &rect, const CRV_Color &color, float width, const CRV_Color &backgroundColor) = 0;

		//** Exporting operations **//
		enum class Format {
			BMP
		};

		[[nodiscard]] crv::type::ByteStream Export(Format format, uint8_t flags = 0);

		virtual ~CommonImage() = default;

	protected:
		CommonImage() = default;

		[[nodiscard]] virtual crv::type::ByteStream ExportAsBMP(uint8_t flags) const = 0;
	};
}

using CRV_ImageFormat = crv::graphics::CommonImage::Format;

template<typename T>
concept CommonImageType =
std::is_same_v<T, crv::graphics::CommonImage> ||
std::is_same_v<T, crv::graphics::Bitmap>;