#ifndef CSE_HAL_LOGGER_H
#define CSE_HAL_LOGGER_H

#include "IStandardUART.h"
#include <cstdint>
#include <cstdarg>

namespace cse {

enum class LogLevel : uint8_t {
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARN = 3,
    ERROR = 4,
    FATAL = 5
};

class Logger {
public:
    static void initialize(IStandardUART* uart, LogLevel level = LogLevel::INFO);
    static void setLevel(LogLevel level);
    static LogLevel getLevel();
    static void log(LogLevel level, const char* format, ...);
    static void logRaw(LogLevel level, const char* message);
    static void flush();
    static void setTimestampEnabled(bool enabled);
    static void setUptimeMs(uint32_t ms);
    static uint32_t getUptimeMs();

    static const char* levelToString(LogLevel level);
    static const char* levelToShortString(LogLevel level);

private:
    static void outputTimestamp();
    static void outputString(const char* str);
    static void outputChar(char c);

    static IStandardUART* s_UART;
    static LogLevel s_Level;
    static bool s_TimestampEnabled;
    static char s_Buffer[256];
    static uint32_t s_UptimeMs;
};

}

#define LOG_TRACE(...) cse::Logger::log(cse::LogLevel::TRACE, __VA_ARGS__)
#define LOG_DEBUG(...) cse::Logger::log(cse::LogLevel::DEBUG, __VA_ARGS__)
#define LOG_INFO(...)  cse::Logger::log(cse::LogLevel::INFO, __VA_ARGS__)
#define LOG_WARN(...)  cse::Logger::log(cse::LogLevel::WARN, __VA_ARGS__)
#define LOG_ERROR(...) cse::Logger::log(cse::LogLevel::ERROR, __VA_ARGS__)
#define LOG_FATAL(...) cse::Logger::log(cse::LogLevel::FATAL, __VA_ARGS__)

#endif
