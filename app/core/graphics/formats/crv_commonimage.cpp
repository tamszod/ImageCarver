#include "crv_commonimage.h"

bool crv::graphics::CommonImage::IsBitmap() const {
	return false;
}

const crv::graphics::Bitmap* crv::graphics::CommonImage::AsBitmap() const {
	return nullptr;
}

crv::graphics::Bitmap* crv::graphics::CommonImage::AsMutableBitmap() {
	return nullptr;
}

crv::type::ByteStream crv::graphics::CommonImage::Export(Format format, uint8_t flags) {
	switch (format) {
		case Format::BMP: {
			return _ExportAsBMP(flags);
		}
		default: {
			return crv::type::ByteStream{};
		}
	}
}