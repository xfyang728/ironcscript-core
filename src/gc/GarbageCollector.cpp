#include "GarbageCollector.h"
#include <cstdlib>
#include <cstring>
#include <algorithm>

namespace cse {

GarbageCollector::GarbageCollector()
    : heapSize(0)
    , collectThreshold(1024 * 1024)
    , collectedCount(0) {
}

GarbageCollector::~GarbageCollector() {
    collect();
}

GarbageCollector& GarbageCollector::instance() {
    static GarbageCollector gc;
    return gc;
}

void* GarbageCollector::allocate(GCObjectType type, size_t size) {
    void* data = std::malloc(size);
    if (!data) {
        return nullptr;
    }

    GCObject* obj = new GCObject(type, size, data);
    objects.push_back(obj);
    heapSize += size;

    return data;
}

void GarbageCollector::retain(void* ptr) {
    if (!ptr) return;

    for (auto* obj : objects) {
        if (obj->data == ptr) {
            obj->refCount++;
            return;
        }
    }
}

void GarbageCollector::release(void* ptr) {
    if (!ptr) return;

    for (auto* obj : objects) {
        if (obj->data == ptr) {
            obj->refCount--;
            if (obj->refCount == 0) {
                heapSize -= obj->size;
                if (obj->data) {
                    std::free(obj->data);
                    obj->data = nullptr;
                }
                delete obj;
                objects.erase(std::remove(objects.begin(), objects.end(), obj), objects.end());
            }
            return;
        }
    }
}

void GarbageCollector::setCollectThreshold(size_t threshold) {
    collectThreshold = threshold;
}

bool GarbageCollector::shouldCollect() const {
    return heapSize >= collectThreshold;
}

void GarbageCollector::collect() {
}

void GarbageCollector::registerRoot(void* root) {
    roots.insert(root);
}

void GarbageCollector::unregisterRoot(void* root) {
    roots.erase(root);
}

void GarbageCollector::mark() {
}

void GarbageCollector::sweep() {
}

void GarbageCollector::markRoot(void* ptr) {
}

}