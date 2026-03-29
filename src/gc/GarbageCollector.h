#pragma once

#include <cstdint>
#include <vector>
#include <unordered_set>
#include <functional>

namespace cse {

enum class GCObjectType {
    String,
    Array,
    Hash,
    Closure,
    UserData,
    Unknown
};

struct GCObject {
    uint32_t refCount;
    bool marked;
    GCObjectType type;
    size_t size;
    void* data;

    GCObject(GCObjectType t, size_t sz, void* d)
        : refCount(1), marked(false), type(t), size(sz), data(d) {}
};

class GarbageCollector {
public:
    static GarbageCollector& instance();

    void* allocate(GCObjectType type, size_t size);
    void retain(void* ptr);
    void release(void* ptr);

    void collect();

    size_t getHeapSize() const { return heapSize; }
    size_t getObjectCount() const { return objects.size(); }
    size_t getCollectedCount() const { return collectedCount; }

    void setCollectThreshold(size_t threshold);
    bool shouldCollect() const;

    void registerRoot(void* root);
    void unregisterRoot(void* root);

    using WalkCallback = std::function<void(void* ptr)>;
    void walkHeap(WalkCallback callback);

private:
    GarbageCollector();
    ~GarbageCollector();

    GarbageCollector(const GarbageCollector&) = delete;
    GarbageCollector& operator=(const GarbageCollector&) = delete;

    void mark();
    void sweep();
    void markRoot(void* ptr);

    size_t heapSize = 0;
    size_t collectThreshold = 1024 * 1024;
    size_t collectedCount = 0;
    std::vector<GCObject*> objects;
    std::unordered_set<void*> roots;
};

inline void* gc_malloc(size_t size) {
    return GarbageCollector::instance().allocate(GCObjectType::Unknown, size);
}

inline void gc_retain(void* ptr) {
    if (ptr) GarbageCollector::instance().retain(ptr);
}

inline void gc_release(void* ptr) {
    if (ptr) GarbageCollector::instance().release(ptr);
}

}