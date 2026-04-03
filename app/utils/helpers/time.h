#include <chrono>
#include <format>

namespace crv {
    namespace helper {
        inline std::string GetQuickTime() {
            auto now = std::chrono::system_clock::now();

            auto local = std::chrono::zoned_time{
                std::chrono::current_zone(), now
            };

            return std::format("{:%d.%m.%Y %H:%M}", local);
        }
    }
}