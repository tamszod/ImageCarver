#pragma once

#include "../../../utilities/type.h"
#include "../../../utilities/types/bytes.h"
#include "../../../utilities/types/crv_color.h"

namespace crv {
	namespace graphics {

		class Bitmap;

		class CommonImage {
		public:

			virtual bool IsBitmap() const;
			virtual const Bitmap* AsBitmap() const;
			virtual Bitmap* AsMutableBitmap();

			//** Getters for dimensions and pixel data **//
			virtual int GetWidth() const = 0;
			virtual int GetHeight() const = 0;
			virtual float GetWidthF() const = 0;
			virtual float GetHeightF() const = 0;
			virtual std::unique_ptr<CRV_Color> GetPixelColor(int x, int y) const = 0;
			virtual std::unique_ptr<CRV_Color> GetPixelColor(float x, float y) const = 0;

			//** Low-level drawing operations **//
			virtual bool SetPixel(int x, int y, const CRV_Color& color) = 0;
			virtual bool SetPixel(float x, float y, const CRV_Color& color) = 0;
			virtual void AddLine(int x0, int y0, int x1, int y1, const CRV_Color& color, int width = 1) = 0;
			virtual void AddLine(float x0, float y0, float x1, float y1, const CRV_Color& color, float width = 1) = 0;
			virtual void FillRectangle(const crv::type::Rectangle& rect, const CRV_Color& backgroundColor) = 0;
			virtual void FillRectangle(const BoundingBoxF& rect, const CRV_Color& backgroundColor) = 0;
			virtual void AddRectangle(const crv::type::Rectangle& rect, const CRV_Color& color, int width = 1) = 0;
			virtual void AddRectangle(const BoundingBoxF& rect, const CRV_Color& color, float width = 1.f) = 0;
			virtual void AddRectangle(const crv::type::Rectangle& rect, const CRV_Color& color, int width, const CRV_Color& backgroundColor) = 0;
			virtual void AddRectangle(const BoundingBoxF& rect, const CRV_Color& color, float width, const CRV_Color& backgroundColor) = 0;

			virtual void FillOval(const crv::type::Rectangle& rect, const CRV_Color& backgroundColor) = 0;
			virtual void FillOval(const BoundingBoxF& rect, const CRV_Color& backgroundColor) = 0;
			virtual void AddOval(const crv::type::Rectangle& rect, const CRV_Color& color, int width = 1) = 0;
			virtual void AddOval(const BoundingBoxF& rect, const CRV_Color& color, float width = 1.f) = 0;
			virtual void AddOval(const crv::type::Rectangle& rect, const CRV_Color& color, int width, const CRV_Color& backgroundColor) = 0;
			virtual void AddOval(const BoundingBoxF& rect, const CRV_Color& color, float width, const CRV_Color& backgroundColor) = 0;

			virtual ~CommonImage() = default;

			//** Exporting operations **//
			enum class Format {
				BMP
			};

			crv::type::ByteStream Export(Format format, uint8_t flags = 0);

		protected:
			virtual crv::type::ByteStream _ExportAsBMP(uint8_t flags) const = 0;

			CommonImage() = default;
		};
	}
}

using CRV_ImageFormat = crv::graphics::CommonImage::Format;

template<typename T>
concept CommonImageType =
std::is_same_v<T, crv::graphics::CommonImage> ||
std::is_same_v<T, crv::graphics::Bitmap>;