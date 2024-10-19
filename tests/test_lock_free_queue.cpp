#include "catch.hpp"
#include "lock_free_queue.h"
#include <thread>
#include <vector>

TEST_CASE("LockFreeQueue basic operations", "[lock_free_queue]") {
    LockFreeQueue<int, 5> queue;
    int item;

    SECTION("Enqueue and dequeue single item") {
        REQUIRE(queue.enqueue(42));
        REQUIRE(queue.dequeue(item));
        REQUIRE(item == 42);
    }

    SECTION("Queue fills up") {
        REQUIRE(queue.enqueue(1));
        REQUIRE(queue.enqueue(2));
        REQUIRE(queue.enqueue(3));
        REQUIRE(queue.enqueue(4));
        REQUIRE(queue.enqueue(5));
        REQUIRE_FALSE(queue.enqueue(6));
    }

    SECTION("Queue empties") {
        REQUIRE(queue.enqueue(1));
        REQUIRE(queue.dequeue(item));
        REQUIRE_FALSE(queue.dequeue(item));
    }
}

TEST_CASE("LockFreeQueue multithreaded operations", "[lock_free_queue]") {
    LockFreeQueue<int, 1000> queue;
    std::atomic<int> sum{0};
    const int num_threads = 4;
    const int num_operations = 10000;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&queue, &sum, num_operations]() {
            for (int j = 0; j < num_operations; ++j) {
                queue.enqueue(1);
                int item;
                if (queue.dequeue(item)) {
                    sum.fetch_add(item, std::memory_order_relaxed);
                }
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    REQUIRE(sum.load() == num_threads * num_operations);
}