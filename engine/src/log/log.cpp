#include "log/log.h"

#include "spdlog/sinks/stdout_color_sinks-inl.h"

std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::init() {
    spdlog::set_pattern("%^%T-%e %s [%l] %v%$");

    s_Logger = spdlog::stdout_color_mt("console");
    s_Logger->set_level(spdlog::level::trace);
}
