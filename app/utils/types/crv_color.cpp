#include "crv_color.h"


std::unique_ptr<CRV_Color> CRV_Color::Create(uint8_t red, uint8_t blue, uint8_t green) {
	std::unique_ptr<CRV_Color> color(new CRV_RGBColor(red, blue, green));
	return color;
}

std::unique_ptr<CRV_Color> CRV_Color::Create(uint8_t red, uint8_t blue, uint8_t green, uint8_t alpha) {
	return std::unique_ptr<CRV_Color>(new CRV_RGBAColor(red, blue, green, alpha));
}

CRV_RGBAColor::CRV_RGBAColor(int red, int green, int blue, int alpha)
	: CRV_RGBColor(red, green, blue)
	, _alpha(alpha) {
}