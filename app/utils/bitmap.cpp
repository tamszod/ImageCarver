//#pragma once
//
//#include "bitmap.h"
//
//#include <cmath>
//#include <fstream>
//#include <filesystem>
//
//
//std::unique_ptr<util::img::Pen> util::img::Pen::CreatePen(const util::img::RGB& rgb, int width) {
//    std::unique_ptr<util::img::Pen> pen;
//	pen.reset(new util::img::Pen());
//	pen->_red = rgb.r;
//	pen->_green = rgb.g;
//	pen->_blue = rgb.b;
//	pen->_width = width;
//	return pen;
//}
//
//uint8_t util::img::Pen::GetColorValue(int v) const {
//    switch (v) {
//        case 0: return _red;
//        case 1: return _green;
//        case 2: return _blue;
//        case 3: return _alpha;
//        default: return 0;
//	} 
//}
//
//std::unique_ptr<util::img::Bitmap> util::img::Bitmap::CreateRGBBitmap(int width, int height) {
//	auto bmp = std::make_unique<util::img::RGBBitmap>(width, height);
//	return bmp;
//}
//
//void util::img::Bitmap::MoveTo(const util::type::Point& point) {
//	_currentPosition = point;
//}
//
//void util::img::Bitmap::DrawPixel(int x, int y) {
//    if (x < 0 || x >= _width || y < 0 || y >= _height || !_pen)
//        return;
//
//    int idx = (y * _width + x) * _channels;
//
//	for (size_t i = 0; i < _channels; ++i) {
//        _data[idx + i] = _pen->GetColorValue(i);
//    }
//}
//
//void util::img::Bitmap::DrawLineTo(const util::type::Point& point) {
//    if (point.x < 0 || point.x >= _width || point.y < 0 || point.y >= _height || !_pen) {
//        return;
//    }
//
//    int x0 = _currentPosition.x;
//    int y0 = _currentPosition.y;
//    int x1 = point.x;
//    int y1 = point.y;
//
//    int dx = std::abs(x1 - x0);
//    int dy = std::abs(y1 - y0);
//
//    int sx = (x0 < x1) ? 1 : -1;
//    int sy = (y0 < y1) ? 1 : -1;
//
//    int err = dx - dy;
//
//    int penWidth = std::max(1, (int)_pen->GetWidth());
//    int half = penWidth / 2;
//
//    // Decide perpendicular direction
//    int nx, ny;
//    if (dx > dy) {
//        nx = 0;
//        ny = 1;
//    }
//    else {
//        nx = 1;
//        ny = 0;
//    }
//
//
//    while (true) {
//       
//        // Draw thickness centered on the line
//        for (int w = -half; w <= half; ++w) {
//            int px = x0 + nx * w;
//            int py = y0 + ny * w;
//
//            if (px >= 0 && px < _width && py >= 0 && py < _height) {
//                DrawPixel(px, py);
//            }
//        }
//
//        if (x0 == x1 && y0 == y1) {
//            break;
//        }
//        int e2 = 2 * err;
//        if (e2 > -dy) {
//            err -= dy;
//            x0 += sx;
//        }
//        if (e2 < dx) {
//            err += dx;
//            y0 += sy;
//        }
//    }
//    _currentPosition = point;
//}
//
//void util::img::Bitmap::DrawRectangle(const BoundingBoxF& boundingBox) {
//    Point prevPoint = _currentPosition;
//	MoveTo({ static_cast<int>(boundingBox.left), static_cast<int>(boundingBox.top) });
//	DrawLineTo({ static_cast<int>(boundingBox.right), static_cast<int>(boundingBox.top) });
//	DrawLineTo({ static_cast<int>(boundingBox.right), static_cast<int>(boundingBox.bottom) });
//	DrawLineTo({ static_cast<int>(boundingBox.left), static_cast<int>(boundingBox.bottom) });
//	DrawLineTo({ static_cast<int>(boundingBox.left), static_cast<int>(boundingBox.top) });
//    _currentPosition = prevPoint;
//}
//
//bool util::img::Bitmap::SaveAsBMP(const std::wstring& filePath) const {
//    if (_channels != 1 && _channels != 3 && _channels != 4) {
//        return false; // TODO:  Unsupported operation error
//    }
//
//  //  if (!std::filesystem::create_directories(filePath)) {
//		//return false; // TODO:  Directory creation error
//  //  }
//
//    std::ofstream file(std::filesystem::path(filePath), std::ios::binary);
//    if (!file) {
//		return false; // TODO:  File open error
//    }
//    int bytesPerPixel = 3; // BMP = 24-bit
//    int rowSize = (_width * bytesPerPixel + 3) & (~3); // padded to 4 bytes
//    int dataSize = rowSize * _height;
//    int fileSize = 54 + dataSize;
//
//    // --- FILE HEADER (14 bytes) ---
//    unsigned char fileHeader[14] = {
//        'B','M',
//        0,0,0,0,
//        0,0,0,0,
//        54,0,0,0
//    };
//
//    // file size
//    fileHeader[2] = (unsigned char)(fileSize);
//    fileHeader[3] = (unsigned char)(fileSize >> 8);
//    fileHeader[4] = (unsigned char)(fileSize >> 16);
//    fileHeader[5] = (unsigned char)(fileSize >> 24);
//
//    // --- INFO HEADER (40 bytes) ---
//    unsigned char infoHeader[40] = {
//        40,0,0,0,
//        0,0,0,0, // width
//        0,0,0,0, // height
//        1,0,
//        24,0,
//        0,0,0,0,
//        0,0,0,0,
//        0,0,0,0,
//        0,0,0,0,
//        0,0,0,0
//    };
//
//    // width
//    infoHeader[4] = (unsigned char)(_width);
//    infoHeader[5] = (unsigned char)(_width >> 8);
//    infoHeader[6] = (unsigned char)(_width >> 16);
//    infoHeader[7] = (unsigned char)(_width >> 24);
//
//    // height
//    infoHeader[8] = (unsigned char)(_height);
//    infoHeader[9] = (unsigned char)(_height >> 8);
//    infoHeader[10] = (unsigned char)(_height >> 16);
//    infoHeader[11] = (unsigned char)(_height >> 24);
//
//    // write headers
//    file.write(reinterpret_cast<char*>(fileHeader), 14);
//    file.write(reinterpret_cast<char*>(infoHeader), 40);
//
//    std::vector<uint8_t> row(rowSize);
//    for (int y = _height - 1; y >= 0; --y) {
//        int rowIndex = 0;
//
//        for (int x = 0; x < _width; ++x) {
//            int idx = (y * _width + x) * _channels;
//
//            uint8_t r, g, b;
//
//            if (_channels == 1) {
//                // grayscale expanded to RGB
//                uint8_t gray = _data[idx];
//                r = g = b = gray;
//            }
//            else {
//                r = _data[idx + 0];
//                g = _data[idx + 1];
//                b = _data[idx + 2];
//            }
//
//            // BMP = BGR
//            row[rowIndex++] = b;
//            row[rowIndex++] = g;
//            row[rowIndex++] = r;
//        }
//
//        // padding
//        while (rowIndex < rowSize)
//            row[rowIndex++] = 0;
//
//        file.write(reinterpret_cast<char*>(row.data()), rowSize);
//    }
//
//    return true; // TODO: Success.
//}