#include "MemorySandbox.h"
#include <cstdlib>

namespace cse {

MemorySandbox* MemorySandbox::m_instance = nullptr;

MemorySandbox::MemorySandbox()
    : m_timeLimit(600000),
      m_memoryLimit(1024 * 1024 * 100),
      m_currentMemoryUsage(0),
      m_timedOut(false),
      m_memoryExceeded(false),
      m_shouldStop(false) {
}

MemorySandbox::~MemorySandbox() {
}

MemorySandbox& MemorySandbox::instance() {
    if (!m_instance) {
        m_instance = new MemorySandbox();
    }
    return *m_instance;
}

void MemorySandbox::setTimeLimit(size_t milliseconds) {
    m_timeLimit = milliseconds;
}

void MemorySandbox::setMemoryLimit(size_t bytes) {
    m_memoryLimit = bytes;
}

size_t MemorySandbox::getCurrentMemoryUsage() const {
    return m_currentMemoryUsage;
}

void MemorySandbox::startExecution() {
    m_timedOut = false;
    m_memoryExceeded = false;
    m_shouldStop = false;
    m_currentMemoryUsage = 0;
}

void MemorySandbox::endExecution() {
    m_shouldStop = true;
}

bool MemorySandbox::hasTimedOut() const {
    return m_timedOut;
}

bool MemorySandbox::hasMemoryExceeded() const {
    return m_memoryExceeded;
}

bool MemorySandbox::shouldStop() const {
    return m_shouldStop || m_timedOut || m_memoryExceeded;
}

bool MemorySandbox::checkExecutionStatus() {
    return false;
}

void MemorySandbox::allocateMemory(size_t bytes) {
    m_currentMemoryUsage += bytes;
}

void MemorySandbox::freeMemory(size_t bytes) {
    if (m_currentMemoryUsage >= bytes) {
        m_currentMemoryUsage -= bytes;
    }
}

}