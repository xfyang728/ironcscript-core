#pragma once

#include <atomic>
#include <cstddef>

namespace cse {

class MemorySandbox {
private:
    std::atomic<size_t> m_timeLimit;
    std::atomic<size_t> m_memoryLimit;
    std::atomic<size_t> m_currentMemoryUsage;
    std::atomic<bool> m_timedOut;
    std::atomic<bool> m_memoryExceeded;
    std::atomic<bool> m_shouldStop;

    static MemorySandbox* m_instance;

    MemorySandbox();

public:
    ~MemorySandbox();

    static MemorySandbox& instance();

    void setTimeLimit(size_t milliseconds);
    void setMemoryLimit(size_t bytes);
    size_t getCurrentMemoryUsage() const;

    void startExecution();
    void endExecution();

    bool hasTimedOut() const;
    bool hasMemoryExceeded() const;

    void allocateMemory(size_t bytes);
    void freeMemory(size_t bytes);

    bool shouldStop() const;
    bool checkExecutionStatus();
};

}