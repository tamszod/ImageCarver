#pragma once

#include <vector>

namespace crv {
    namespace type {
        using ByteStream = std::vector<uint8_t>;

        class ByteWriter {
        public:

            ByteWriter() = default;

            const ByteStream& Data() const { return _buffer; }
            ByteStream&& MoveData() { return std::move(_buffer); }

            void Reserve(size_t size) {
                _buffer.reserve(size);
            }

            // --- Basic writes ---
            void WriteU8(uint8_t v) {
                _buffer.push_back(v);
            }

            void WriteU16(uint16_t v) {
                _buffer.push_back(static_cast<uint8_t>(v));
                _buffer.push_back(static_cast<uint8_t>(v >> 8));
            }

            void WriteU32(uint32_t v) {
                _buffer.push_back(static_cast<uint8_t>(v));
                _buffer.push_back(static_cast<uint8_t>(v >> 8));
                _buffer.push_back(static_cast<uint8_t>(v >> 16));
                _buffer.push_back(static_cast<uint8_t>(v >> 24));
            }

            // --- Raw block ---
            void WriteBytes(const uint8_t* data, size_t size) {
                _buffer.insert(_buffer.end(), data, data + size);
            }

            void WriteBytes(const ByteStream& data) {
                _buffer.insert(_buffer.end(), data.begin(), data.end());
            }
        private:
            ByteStream _buffer;
        };

    }
}