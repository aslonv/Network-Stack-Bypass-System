#ifndef LOCK_FREE_QUEUE_H
#define LOCK_FREE_QUEUE_H

#include <atomic>
#include <array>

template<typename T, size_t Size>
class LockFreeQueue {
    private:
        std::array<T, Size> buffer;
        std::atomic<size_t> head{0};
        std::atomic<size_t> tail{0};
    
    public:
        bool enqueue(const T& item) {
            size_t current_tail = tail.load(std::memory_order_relaxed);
            size_t next_tail = (current_tail + 1) % Size;
            if (next_tail == head.load(std::memory_order_acquire))
                return false; // Queue is full
            buffer[current_tail] = item;
            tail.store(next_tail, std::memory_order_release);
            return true;
        }

        bool dequeue(T& item) {
            size_t current_head = head.load(std::memory_order_relaxed);
            if (current_head == tail.load(std::memory_order_acquire))
                return false; // Queue is empty
            item = buffer[current_head]
            head.store((current_head + 1) % Size, std::memory_order_release);
            return true;
        }
};

#endif // LOCK_FREE_QUEUE_H