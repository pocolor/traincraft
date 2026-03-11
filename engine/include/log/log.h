#pragma once

#include <spdlog/spdlog.h>
#include <memory>

class Log {
public:
    Log() = delete;

    static void init();

    static std::shared_ptr<spdlog::logger>& getLogger() { return s_Logger; }
private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};

#ifdef RC_DEBUG

#define RC_LOG_TRACE(...) Log::getLogger()->trace(__VA_ARGS__)
#define RC_LOG_DEBUG(...) Log::getLogger()->debug(__VA_ARGS__)
#define RC_LOG_INFO(...) Log::getLogger()->info(__VA_ARGS__)
#define RC_LOG_WARN(...) Log::getLogger()->warn(__VA_ARGS__)
#define RC_LOG_ERROR(...) Log::getLogger()->error(__VA_ARGS__)
#define RC_LOG_CRITICAL(...) Log::getLogger()->critical(__VA_ARGS__)

#define RC_ASSERT(expr) if (!static_cast<bool>(expr))\
RC_LOG_ERROR("Assertion failed. `{0}` in file {1} on line {2}", #expr, __FILE__, __LINE__)

#else

#define RC_LOG_TRACE(...)
#define RC_LOG_DEBUG(...)
#define RC_LOG_INFO(...)
#define RC_LOG_WARN(...)
#define RC_LOG_ERROR(...)
#define RC_LOG_CRITICAL(...)

#define RC_ASSERT(expr)

#endif