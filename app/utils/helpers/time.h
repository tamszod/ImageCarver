#include <chrono>
#include <format>

namespace crv {
    namespace helper {
        inline std::string GetQuickTime() {
            auto now = std::chrono::system_clock::now();
#ifdef __APPLE__
            std::time_t t = std::chrono::system_clock::to_time_t(now);

            std::tm tm{};
            localtime_r(&t, &tm);

            return std::format("{:02}.{:02}.{} {:02}:{:02}",
                               tm.tm_mday,
                               tm.tm_mon + 1,
                               tm.tm_year + 1900,
                               tm.tm_hour,
                               tm.tm_min
            );
#else
            auto local = std::chrono::zoned_time{
                std::chrono::current_zone(), now
            };
            return std::format("{:%d.%m.%Y %H:%M}", local);
#endif
        }
    }
}