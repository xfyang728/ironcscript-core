#include "hal/Logger.h"
#include <cstdio>
#include <cstring>
#include <cstdarg>

namespace cse {

IStandardUART* Logger::s_UART = nullptr;
LogLevel Logger::s_Level = LogLevel::INFO;
bool Logger::s_TimestampEnabled = true;
char Logger::s_Buffer[256];
uint32_t Logger::s_UptimeMs = 0;

void Logger::initialize(IStandardUART* uart, LogLevel level) {
    s_UART = uart;
    s_Level = level;
    s_UptimeMs = 0;
}

void Logger::setLevel(LogLevel level) {
    s_Level = level;
}

LogLevel Logger::getLevel() {
    return s_Level;
}

void Logger::setTimestampEnabled(bool enabled) {
    s_TimestampEnabled = enabled;
}

void Logger::setUptimeMs(uint32_t ms) {
    s_UptimeMs = ms;
}

uint32_t Logger::getUptimeMs() {
    return s_UptimeMs;
}

const char* Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE: return "TRACE";
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO:  return "INFO";
        case LogLevel::WARN:  return "WARN";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::FATAL: return "FATAL";
        default: return "UNKNOWN";
    }
}

const char* Logger::levelToShortString(LogLevel level) {
    switch (level) {
        case LogLevel::TRACE: return "T";
        case LogLevel::DEBUG: return "D";
        case LogLevel::INFO:  return "I";
        case LogLevel::WARN:  return "W";
        case LogLevel::ERROR: return "E";
        case LogLevel::FATAL: return "F";
        default: return "?";
    }
}

void Logger::outputChar(char c) {
    printf("%c", c);
}

void Logger::outputString(const char* str) {
    if (str) {
        printf("%s", str);
    }
}

void Logger::outputTimestamp() {
    if (!s_TimestampEnabled) return;

    uint32_t ms = s_UptimeMs;
    uint32_t hours = ms / 3600000;
    ms %= 3600000;
    uint32_t minutes = ms / 60000;
    ms %= 60000;
    uint32_t seconds = ms / 1000;
    ms %= 1000;

    snprintf(s_Buffer, sizeof(s_Buffer), "[%02u:%02u:%02u.%03u] ",
             hours, minutes, seconds, ms);
    outputString(s_Buffer);
}

void Logger::log(LogLevel level, const char* format, ...) {
    if (level < s_Level) return;

    outputTimestamp();

    snprintf(s_Buffer, sizeof(s_Buffer), "[%s] ", levelToString(level));
    outputString(s_Buffer);

    va_list args;
    va_start(args, format);
    vsnprintf(s_Buffer, sizeof(s_Buffer), format, args);
    va_end(args);

    outputString(s_Buffer);
    outputString("\r\n");
}

void Logger::logRaw(LogLevel level, const char* message) {
    if (level < s_Level) return;

    outputTimestamp();

    snprintf(s_Buffer, sizeof(s_Buffer), "[%s] ", levelToString(level));
    outputString(s_Buffer);

    if (message) {
        outputString(message);
    }
    outputString("\r\n");
}

void Logger::flush() {
}

}
