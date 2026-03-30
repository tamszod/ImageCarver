#pragma once

#include "crv_bitmap.h"

#include <cmath>
#include <algorithm>

std::unique_ptr<crv::graphics::Bitmap> crv::graphics::Bitmap::Create(int width, int height, ColorMode color) {
    switch (color) {
        case ColorMode::MONOCHROME: {
            return nullptr; // Not implemented
        }
        case ColorMode::GRAYSCALE: {
            return nullptr; // Not implemented
        }
        case ColorMode::RGB: {
            return std::unique_ptr< crv::graphics::Bitmap>(new Bitmap24(width, height));
        }
        case ColorMode::RGBA: {
            return nullptr; // Not implemented
		}
        default: {
            return nullptr; // Not implemented
        }
	}
}

bool  crv::graphics::Bitmap::IsBitmap() const {
    return true;
}

const crv::graphics::Bitmap* crv::graphics::Bitmap::AsBitmap() const {
    return this;
}

crv::graphics::Bitmap* crv::graphics::Bitmap::AsMutableBitmap() {
    return this;
}

int crv::graphics::Bitmap::GetWidth() const {
	return _width;
}

int crv::graphics::Bitmap::GetHeight() const {
    return _height;
}

float crv::graphics::Bitmap::GetWidthF() const {
    return static_cast<float>(_width);
}

float crv::graphics::Bitmap::GetHeightF() const {
	return static_cast<float>(_height);
}

std::unique_ptr<CRV_Color> crv::graphics::Bitmap::GetPixelColor(float x, float y) const {
	return GetPixelColor(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)));
}

bool crv::graphics::Bitmap::SetPixel(int x, int y, const CRV_Color& color) {
	if (x < 0 || x >= _width || y < 0 || y >= _height)
		return false;
	int idx = (y * _width + x) * _channels;
	for (size_t i = 0; i < _channels; ++i) {
		_data[idx + i] = _GetColorValue(i, color);
	}
	return true;
}

bool crv::graphics::Bitmap::SetPixel(float x, float y, const CRV_Color& color)
{
    int x0 = (int)floor(x);
    int y0 = (int)floor(y);
    int x1 = x0 + 1;
    int y1 = y0 + 1;

    float dx = x - x0;
    float dy = y - y0;

    float w00 = (1 - dx) * (1 - dy);
    float w10 = dx * (1 - dy);
    float w01 = (1 - dx) * dy;
    float w11 = dx * dy;

    _BlendPixel(x0, y0, color, w00);
    _BlendPixel(x1, y0, color, w10);
    _BlendPixel(x0, y1, color, w01);
    _BlendPixel(x1, y1, color, w11);

    return true;
}

void crv::graphics::Bitmap::AddLine(int x0, int y0, int x1, int y1, const CRV_Color& color, int width) {
    int dx = std::abs(x1 - x0);
    int dy = std::abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    int penWidth = std::max(1, (int)width);
    int half = penWidth / 2;

    // Decide perpendicular direction
    int nx, ny;
    if (dx > dy) {
        nx = 0;
        ny = 1;
    }
    else {
        nx = 1;
        ny = 0;
    }

    while (true) {

        // Draw thickness centered on the line
        for (int w = -half; w <= half; ++w) {
            int px = x0 + nx * w;
            int py = y0 + ny * w;

            if (px >= 0 && px < _width && py >= 0 && py < _height) {
                SetPixel(px, py, color);
            }
        }

        if (x0 == x1 && y0 == y1) {
            break;
        }
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void crv::graphics::Bitmap::AddLine(float x0, float y0, float x1, float y1,
    const CRV_Color& color, float width) {
    if (width <= 0.0f) {
        return;
    }

    const float half = width * 0.5f;
    const float aa = 1.0f; // anti-alias region (1 pixel soft edge)

    float dx = x1 - x0;
    float dy = y1 - y0;
    float lenSq = dx * dx + dy * dy;

    if (lenSq == 0.0f) {
        return;
    }

    float invLenSq = 1.0f / lenSq;

    // Bounding box (expanded for AA)
    int minX = (int)floor(std::min(x0, x1) - half - aa);
    int maxX = (int)ceil(std::max(x0, x1) + half + aa);
    int minY = (int)floor(std::min(y0, y1) - half - aa);
    int maxY = (int)ceil(std::max(y0, y1) + half + aa);

    // Clip to bitmap
    minX = std::max(minX, 0);
    minY = std::max(minY, 0);
    maxX = std::min(maxX, _width - 1);
    maxY = std::min(maxY, _height - 1);

    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            float px = x + 0.5f;
            float py = y + 0.5f;

            // Project onto segment
            float t = ((px - x0) * dx + (py - y0) * dy) * invLenSq;
            t = std::max(0.0f, std::min(1.0f, t));

            float projX = x0 + t * dx;
            float projY = y0 + t * dy;

            float distX = px - projX;
            float distY = py - projY;
            float distSq = distX * distX + distY * distY;

            float r = half;

            // Inner solid region
            if (distSq <= (r - aa) * (r - aa)) {
                SetPixel(x, y, color);
            }
            else if (distSq <= (r + aa) * (r + aa)) {
                // Anti-aliased edge
                float dist = sqrt(distSq);
                float alpha = 1.0f - (dist - (r - aa)) / (2.0f * aa);
                alpha = std::clamp(alpha, 0.0f, 1.0f);

                _BlendPixel(x, y, color, alpha);
            }
        }
    }
}

void crv::graphics::Bitmap::FillRectangle(const crv::type::Rectangle& rect, const CRV_Color& backgroundColor) {
    int left = std::max(0, rect.left);
    int right = std::min(_width - 1, rect.right);
    int top = std::max(0, rect.top);
    int bottom = std::min(_height - 1, rect.bottom);

    for (int y = top; y <= bottom; ++y) {
        for (int x = left; x <= right; ++x) {
            SetPixel(x, y, backgroundColor);
        }
    }
}

void crv::graphics::Bitmap::FillRectangle(const BoundingBoxF& rect, const CRV_Color& backgroundColor) {
    float left = rect.left;
    float right = rect.right;
    float top = rect.top;
    float bottom = rect.bottom;

    if (left > right) {
        std::swap(left, right);
    }
    if (top > bottom) {
        std::swap(top, bottom);
    }

    // Bounding box (pixel range)
    int minX = (int)floor(left);
    int maxX = (int)ceil(right);
    int minY = (int)floor(top);
    int maxY = (int)ceil(bottom);

    // Clip to bitmap
    minX = std::max(minX, 0);
    minY = std::max(minY, 0);
    maxX = std::min(maxX, _width - 1);
    maxY = std::min(maxY, _height - 1);

    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            // Pixel bounds
            float px0 = (float)x;
            float px1 = (float)x + 1.0f;
            float py0 = (float)y;
            float py1 = (float)y + 1.0f;

            // Overlap with rectangle
            float overlapX = std::max(0.0f,
                std::min(px1, right) - std::max(px0, left));

            float overlapY = std::max(0.0f,
                std::min(py1, bottom) - std::max(py0, top));

            float coverage = overlapX * overlapY; // 0..1

            if (coverage > 0.0f) {
                _BlendPixel(x, y, backgroundColor, coverage);
            }
        }
    }
}

void crv::graphics::Bitmap::AddRectangle(const crv::type::Rectangle& rect, const CRV_Color& color, int width) {
	AddLine(rect.left, rect.top, rect.right, rect.top, color, width);
	AddLine(rect.right, rect.top, rect.right, rect.bottom, color, width);
	AddLine(rect.right, rect.bottom, rect.left, rect.bottom, color, width);
	AddLine(rect.left, rect.bottom, rect.left, rect.top, color, width);
}

void crv::graphics::Bitmap::AddRectangle(const BoundingBoxF& rect, const CRV_Color& color, float width) {
	AddLine(rect.left, rect.top, rect.right, rect.top, color, width);
	AddLine(rect.right, rect.top, rect.right, rect.bottom, color, width);
	AddLine(rect.right, rect.bottom, rect.left, rect.bottom, color, width);
	AddLine(rect.left, rect.bottom, rect.left, rect.top, color, width);
}

void crv::graphics::Bitmap::AddRectangle(const crv::type::Rectangle& rect, const CRV_Color& color, int width, const CRV_Color& backgroundColor) {
	FillRectangle(rect, backgroundColor);
	AddRectangle(rect, color, width);
}

void crv::graphics::Bitmap::AddRectangle(const BoundingBoxF& rect, const CRV_Color& color, float width, const CRV_Color& backgroundColor) {
	FillRectangle(rect, backgroundColor);
    crv::type::Rectangle strictRect = {
        (int)std::floor(rect.left),
        (int)std::floor(rect.top),
        (int)std::ceil(rect.right),
        (int)std::ceil(rect.bottom)
    };
	AddRectangle(strictRect, color, width);
}

void crv::graphics::Bitmap::FillOval(const crv::type::Rectangle& rect, const CRV_Color& backgroundColor) {
    int left = std::max(0, rect.left);
    int right = std::min(_width - 1, rect.right);
    int top = std::max(0, rect.top);
    int bottom = std::min(_height - 1, rect.bottom);

    float cx = (left + right) * 0.5f;
    float cy = (top + bottom) * 0.5f;

    float rx = (right - left) * 0.5f;
    float ry = (bottom - top) * 0.5f;

    if (rx <= 0 || ry <= 0) return;

    float invRx2 = 1.0f / (rx * rx);
    float invRy2 = 1.0f / (ry * ry);

    for (int y = top; y <= bottom; ++y)
    {
        for (int x = left; x <= right; ++x)
        {
            float px = x + 0.5f;
            float py = y + 0.5f;

            float dx = px - cx;
            float dy = py - cy;

            float v = dx * dx * invRx2 + dy * dy * invRy2;

            if (v <= 1.0f) {
                SetPixel(x, y, backgroundColor);
            }
        }
    }
}

void crv::graphics::Bitmap::FillOval(const BoundingBoxF& rect,
    const CRV_Color& backgroundColor) {
    float left = rect.left;
    float right = rect.right;
    float top = rect.top;
    float bottom = rect.bottom;

    if (left > right) std::swap(left, right);
    if (top > bottom) std::swap(top, bottom);

    float cx = (left + right) * 0.5f;
    float cy = (top + bottom) * 0.5f;

    float rx = (right - left) * 0.5f;
    float ry = (bottom - top) * 0.5f;

    if (rx <= 0.0f || ry <= 0.0f) return;

    float invRx2 = 1.0f / (rx * rx);
    float invRy2 = 1.0f / (ry * ry);

    const float aa = 1.0f; // anti-alias band

    int minX = (int)floor(left - aa);
    int maxX = (int)ceil(right + aa);
    int minY = (int)floor(top - aa);
    int maxY = (int)ceil(bottom + aa);

    minX = std::max(minX, 0);
    minY = std::max(minY, 0);
    maxX = std::min(maxX, _width - 1);
    maxY = std::min(maxY, _height - 1);

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            float px = x + 0.5f;
            float py = y + 0.5f;

            float dx = px - cx;
            float dy = py - cy;

            float v = dx * dx * invRx2 + dy * dy * invRy2;

            if (v <= 1.0f - 0.01f)
            {
                // Fully inside
                SetPixel(x, y, backgroundColor);
            }
            else if (v <= 1.0f + 0.01f)
            {
                // Edge (anti-alias)
                float dist = fabsf(v - 1.0f);
                float alpha = 1.0f - (dist / 0.01f);
                alpha = std::clamp(alpha, 0.0f, 1.0f);

                _BlendPixel(x, y, backgroundColor, alpha);
            }
        }
    }
}

void crv::graphics::Bitmap::AddOval(const crv::type::Rectangle& rect,
    const CRV_Color& color, int width)
{
    float cx = (rect.left + rect.right) * 0.5f;
    float cy = (rect.top + rect.bottom) * 0.5f;

    float rx = (rect.right - rect.left) * 0.5f;
    float ry = (rect.bottom - rect.top) * 0.5f;

    if (rx <= 0 || ry <= 0) return;

    float invRx2 = 1.0f / (rx * rx);
    float invRy2 = 1.0f / (ry * ry);

    float half = width * 0.5f;

    int minX = std::max(0, rect.left - width);
    int maxX = std::min(_width - 1, rect.right + width);
    int minY = std::max(0, rect.top - width);
    int maxY = std::min(_height - 1, rect.bottom + width);

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            float px = x + 0.5f;
            float py = y + 0.5f;

            float dx = px - cx;
            float dy = py - cy;

            float v = dx * dx * invRx2 + dy * dy * invRy2;

            // Distance from edge (approx)
            float dist = fabsf(v - 1.0f) * std::max(rx, ry);

            if (dist <= half)
            {
                SetPixel(x, y, color);
            }
        }
    }
}

void crv::graphics::Bitmap::AddOval(const BoundingBoxF& rect,
    const CRV_Color& color, float width) {
    float left = rect.left, right = rect.right;
    float top = rect.top, bottom = rect.bottom;

    if (left > right) std::swap(left, right);
    if (top > bottom) std::swap(top, bottom);

    float cx = (left + right) * 0.5f;
    float cy = (top + bottom) * 0.5f;

    float rx = (right - left) * 0.5f;
    float ry = (bottom - top) * 0.5f;

    if (rx <= 0 || ry <= 0) return;

    float invRx2 = 1.0f / (rx * rx);
    float invRy2 = 1.0f / (ry * ry);

    float half = width * 0.5f;
    float aa = 1.0f;

    int minX = (int)floor(left - half - aa);
    int maxX = (int)ceil(right + half + aa);
    int minY = (int)floor(top - half - aa);
    int maxY = (int)ceil(bottom + half + aa);

    minX = std::max(minX, 0);
    minY = std::max(minY, 0);
    maxX = std::min(maxX, _width - 1);
    maxY = std::min(maxY, _height - 1);

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            float px = x + 0.5f;
            float py = y + 0.5f;

            float dx = px - cx;
            float dy = py - cy;

            float v = dx * dx * invRx2 + dy * dy * invRy2;

            float dist = fabsf(v - 1.0f) * std::max(rx, ry);

            if (dist <= half - aa)
            {
                SetPixel(x, y, color);
            }
            else if (dist <= half + aa)
            {
                float alpha = 1.0f - (dist - (half - aa)) / (2.0f * aa);
                _BlendPixel(x, y, color, alpha);
            }
        }
    }
}

void crv::graphics::Bitmap::AddOval(const crv::type::Rectangle& rect, const CRV_Color& color, int width, const CRV_Color& backgroundColor) {
    FillOval(rect, backgroundColor);
    AddOval(rect, color, width);
}

void crv::graphics::Bitmap::AddOval(const BoundingBoxF& rect, const CRV_Color& color, float width, const CRV_Color& backgroundColor) {
   
    crv::type::Rectangle strictRect = {
        (int)std::floor(rect.left),
        (int)std::floor(rect.top),
        (int)std::ceil(rect.right),
        (int)std::ceil(rect.bottom)
    };
    FillOval(strictRect, backgroundColor);
    AddOval(strictRect, color, width*2);
}

crv::graphics::Bitmap::Bitmap(int width, int height, int channels)
    : _width(width), _height(height), _channels(channels) {
    _data.resize(_width * _height * _channels);
}

void crv::graphics::Bitmap::_BlendPixel(int x, int y, const CRV_Color& color, float weight) {
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return;
    }

    weight = std::clamp(weight, 0.0f, 1.0f);

    int idx = (y * _width + x) * _channels;

    for (size_t i = 0; i < _channels; ++i)
    {
        float existing = (float)_data[idx + i];
        float incoming = (float)_GetColorValue(i, color);

        float out = existing * (1.0f - weight) + incoming * weight;

        _data[idx + i] = (uint8_t)std::clamp(out, 0.0f, 255.0f);
    }
}

crv::type::ByteStream crv::graphics::Bitmap::_ExportAsBMP(uint8_t flags) const {
    crv::type::ByteWriter w;

    if (_channels != 1 && _channels != 3 && _channels != 4) {
        return {};
    }

    const int bytesPerPixel = 3;
    const int rowSize = (_width * bytesPerPixel + 3) & (~3);
    const int dataSize = rowSize * _height;
    const int fileSize = 54 + dataSize;

    w.Reserve(fileSize);

    // --- FILE HEADER ---
    w.WriteU8('B');
    w.WriteU8('M');
    w.WriteU32(fileSize);
    w.WriteU16(0);
    w.WriteU16(0);
    w.WriteU32(54);

    // --- INFO HEADER ---
    w.WriteU32(40);
    w.WriteU32(_width);
    w.WriteU32(_height);
    w.WriteU16(1);
    w.WriteU16(24);
    w.WriteU32(0);
    w.WriteU32(dataSize);
    w.WriteU32(0);
    w.WriteU32(0);
    w.WriteU32(0);
    w.WriteU32(0);

    std::vector<uint8_t> row(rowSize);

    for (int y = _height - 1; y >= 0; --y) {
        int rowIndex = 0;

        for (int x = 0; x < _width; ++x) {
            int idx = (y * _width + x) * _channels;

            uint8_t r, g, b;

            if (_channels == 1) {
                uint8_t gray = _data[idx];
                r = g = b = gray;
            }
            else {
                r = _data[idx + 0];
                g = _data[idx + 1];
                b = _data[idx + 2];
            }

            row[rowIndex++] = b;
            row[rowIndex++] = g;
            row[rowIndex++] = r;
        }

        while (rowIndex < rowSize)
            row[rowIndex++] = 0;

        w.WriteBytes(row);
    }

    return w.MoveData();
}

std::unique_ptr<CRV_Color> crv::graphics::Bitmap24::GetPixelColor(int x, int y) const {
    int idx = (y * _width + x) * _channels;
    return CRV_Color::Create(
        _data[idx + 0],
        _data[idx + 1],
        _data[idx + 2]
	);
}

uint8_t crv::graphics::Bitmap24::_GetColorValue(size_t i, const CRV_Color& color) const
{
    switch (i) {
        case 0: {
            return color.GetRValue();
        }
        case 1: {
            return color.GetGValue();
        }
        case 2: {
            return color.GetBValue();
        }
        default: {
            return 0;
        }
    }
}