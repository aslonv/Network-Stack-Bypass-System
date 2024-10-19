#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <atomic>
#include <array>

template<typename T, size_t Size>
class LockFreeQueue {
    private:
        std::array<T, Size> buffer;
        std::atomic<size_t> head{0};
}