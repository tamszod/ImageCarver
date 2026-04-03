#pragma once

#include <cstdint>
#include <memory>

class CRV_RGBColor;

class CRV_Color {
public:
	static std::unique_ptr<CRV_Color> Create(uint8_t red = 0, uint8_t blue = 0, uint8_t green = 0);
	static std::unique_ptr<CRV_Color> Create(uint8_t red, uint8_t blue, uint8_t green, uint8_t alpha);

	virtual uint8_t GetRValue() const {
		return 0;
	}
	virtual uint8_t GetGValue() const {
		return 0;
	}
	virtual uint8_t GetBValue() const {
		return 0;
	}
	virtual uint8_t GetAValue() const {
		return 255;
	}

protected:
	CRV_Color() = default;
};


class CRV_RGBColor: public CRV_Color {
public:
	virtual uint8_t GetRValue() const override {
		return _red;
	}
	virtual uint8_t GetGValue() const override {
		return _green;
	}
	virtual uint8_t GetBValue() const override {
		return _blue;
	}
	virtual uint8_t GetAValue() const override {
		return 255;
	}

	CRV_RGBColor(int red = 0, int green = 0, int blue = 0) : _red(red), _green(green), _blue(blue) {}

protected:
	uint8_t _red = 0;
	uint8_t _green = 0;
	uint8_t _blue = 0;
};

class CRV_RGBAColor : public CRV_RGBColor {
public:
	virtual uint8_t GetAValue() const override {
		return _alpha;
	}

	CRV_RGBAColor(int red, int green, int blue, int alpha);

protected:
	uint8_t _alpha = 255;
};