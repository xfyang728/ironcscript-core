#ifndef CSE_RV64MEMORYMANAGER_H
#define CSE_RV64MEMORYMANAGER_H

#include "../MemoryManager.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace cse {

class RV64MemoryManager : public MemoryManager {
public:
    RV64MemoryManager();
    ~RV64MemoryManager();
    
    void initMemory();
    void setMemoryProtection(void* address, size_t size, int protection);
    bool isMemoryWithinLimit() const;
    void optimizeForK210();
    
private:
    static const size_t MAX_MEMORY_SIZE = 8 * 1024 * 1024; // 8MB memory limit
    static const size_t K210_MEMORY_LIMIT = 6 * 1024 * 1024; // K210 platform memory limit
    bool m_OptimizedForK210;
};

} // namespace cse

#endif // CSE_RV64MEMORYMANAGER_H