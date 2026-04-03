//#pragma once
//
//#include "type.h"
//
//#include <string>
//#include <vector>
//#include <memory>
//#include <cstdint>
//
//namespace util {
//	namespace img {
//        struct RGB {
//            uint8_t r = 0;
//            uint8_t g = 0;
//            uint8_t b = 0;
//            RGB() = default;
//			RGB(uint8_t red, uint8_t green, uint8_t blue) : r(red), g(green), b(blue) {}
//        };
//
//
//        class Pen {
//        public:
//            static std::unique_ptr<Pen> CreatePen(const RGB& rgb, int width);
//
//            uint8_t GetColorValue(int v) const;
//			int GetWidth() const { return _width; }
//
//        private:
//            Pen() = default;
//
//            uint8_t _red = 0;
//            uint8_t _green = 0;
//            uint8_t _blue = 0;
//			uint8_t _alpha = 255;
//            int _width = 1;
//        };
//
//        class Bitmap {
//        public:
//            enum class ColorMode {
//				NONE = 0,
//                MONOCHROME = 1,
//                GRAYSCALE = 2,
//                RGB = 3,
//                RGBA = 4
//			};
//
//			using Color = std::vector<uint8_t>;
//
//            static std::unique_ptr<Bitmap> CreateMonochromeBitmap(int width, int height);
//            static std::unique_ptr<Bitmap> CreateGrayScaleBitmap(int width, int height);
//            static std::unique_ptr<Bitmap> CreateRGBBitmap(int width, int height);
//            static std::unique_ptr<Bitmap> CreateRGBABitmap(int width, int height);
//
//            virtual ColorMode GetColorMode() const = 0;
//			int GetWidth() const { return _width; }
//			int GetHeight() const { return _height; }
//
//			void SelectPen(std::unique_ptr<Pen> pen) { _pen = std::move(pen); }
//            void SelectPen(std::shared_ptr<Pen> pen) { _pen = std::move(pen); }
//
//            virtual void MoveTo(const util::type::Point& point);
//            virtual void DrawPixel(int x, int y);
//            virtual void DrawLineTo(const util::type::Point& point);
//			virtual void DrawRectangle(const BoundingBoxF& boundingBox);
//           // virtual void DrawEllipse(const BoundingBoxF& boundingBox);
//
//			virtual bool SaveAsBMP(const std::wstring& filePath) const;
//
//			virtual ~Bitmap() = default;
//        protected:
//            Bitmap() = default;
//
//            Bitmap(int width, int height, int channels)
//                : _width(width), _height(height), _channels(channels)
//            {
//                _data.resize(_width * _height * _channels);
//            }
//
//            int _width = 0;
//            int _height = 0;
//            int _channels = 0;
//            std::vector<uint8_t> _data{};
//
//            util::type::Point _currentPosition{};
//            std::shared_ptr<Pen> _pen{};
//        };
//
//        class RGBBitmap : public Bitmap {
//        public:
//            RGBBitmap(int width, int height) : Bitmap(width, height, 3) {}
//            ColorMode GetColorMode() const override { return ColorMode::RGB; }
//        private:
//        };
//	}
//}