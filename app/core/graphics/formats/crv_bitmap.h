#pragma once

#include "crv_commonimage.h"

#include <vector>
namespace crv {
	namespace graphics {
		class Bitmap : public CommonImage {
		public:
			enum class ColorMode {
				NONE = 0,
				MONOCHROME = 1,
				GRAYSCALE = 2,
				RGB = 3,
				RGBA = 4
			};

			static std::unique_ptr<Bitmap> Create(int width, int height, ColorMode color);

			virtual bool IsBitmap() const override;
			virtual const  crv::graphics::Bitmap* AsBitmap() const override;
			virtual  crv::graphics::Bitmap* AsMutableBitmap() override;

			virtual int GetWidth() const override;
			virtual int GetHeight() const override;
			virtual float GetWidthF() const override;
			virtual float GetHeightF() const override;
			virtual std::unique_ptr<CRV_Color> GetPixelColor(int x, int y) const override = 0;
			virtual std::unique_ptr<CRV_Color> GetPixelColor(float x, float y) const override;

			virtual int GetBitsPerPixel() const = 0;
			virtual ColorMode GetColorMode() const = 0;

			virtual bool SetPixel(int x, int y, const CRV_Color& color) override;
			virtual bool SetPixel(float x, float y, const CRV_Color& color) override;
			virtual void AddLine(int x0, int y0, int x1, int y1, const CRV_Color& color, int width = 1) override;
			virtual void AddLine(float x0, float y0, float x1, float y1, const CRV_Color& color, float width = 1) override;
			virtual void FillRectangle(const crv::type::Rectangle& rect, const CRV_Color& backgroundColor) override;
			virtual void FillRectangle(const BoundingBoxF& rect, const CRV_Color& backgroundColor) override;
			virtual void AddRectangle(const crv::type::Rectangle& rect, const CRV_Color& color, int width = 1) override;
			virtual void AddRectangle(const BoundingBoxF& rect, const CRV_Color& color, float width = 1.f) override;
			virtual void AddRectangle(const crv::type::Rectangle& rect, const CRV_Color& color, int width, const CRV_Color& backgroundColor) override;
			virtual void AddRectangle(const BoundingBoxF& rect, const CRV_Color& color, float width, const CRV_Color& backgroundColor) override;

			virtual void FillOval(const crv::type::Rectangle& rect, const CRV_Color& backgroundColor) override;
			virtual void FillOval(const BoundingBoxF& rect, const CRV_Color& backgroundColor) override;
			virtual void AddOval(const crv::type::Rectangle& rect, const CRV_Color& color, int width = 1) override;
			virtual void AddOval(const BoundingBoxF& rect, const CRV_Color& color, float width = 1.f) override;
			virtual void AddOval(const crv::type::Rectangle& rect, const CRV_Color& color, int width, const CRV_Color& backgroundColor) override;
			virtual void AddOval(const BoundingBoxF& rect, const CRV_Color& color, float width, const CRV_Color& backgroundColor) override;

			~Bitmap() = default;
		protected:
			Bitmap(int width, int height, int channels);

			void _BlendPixel(int x, int y, const CRV_Color& color, float weight);

			virtual crv::type::ByteStream _ExportAsBMP(uint8_t flags) const override;

			// Get the color value for the i-th channel (0 for red, 1 for green, 2 for blue, 3 for alpha) from the given color
			virtual uint8_t _GetColorValue(size_t i, const CRV_Color& color) const = 0;

			int _width = 0;
			int _height = 0;
			int _channels = 0;
			std::vector<uint8_t> _data{};

		};

		class Bitmap24 : public Bitmap {
		public:
			virtual int GetBitsPerPixel() const override { return 24; }
			virtual ColorMode GetColorMode() const override { return ColorMode::RGB; }
			virtual std::unique_ptr<CRV_Color> GetPixelColor(int x, int y) const override;

			~Bitmap24() = default;
		protected:
			virtual uint8_t _GetColorValue(size_t i, const CRV_Color& color) const override;
		private:
			Bitmap24(int width, int height) : Bitmap(width, height, 3) {}
			friend std::unique_ptr<Bitmap> Bitmap::Create(int, int, ColorMode);
		};
	}
}

using CRV_Bitmap = crv::graphics::Bitmap;
using CRV_Bitmap24 = crv::graphics::Bitmap;
