#include "trading_system.h"
#include <iostream>
#include <thread>

TradingSystem::TradingSystem(NIC& nic) : nice(nic) {}

void TradingSystem::process_orders() {
    OrderPacket order;
    while (running.load(std::memory_order_acquire)) {
        if (order_queue.dequeue(order)) {
            // Process the order (in a real system, this will interact with order books, etc.)
            std::cout << "Processing order: " << order.order_id << std::endl;
        }
    }
}

void TradingSystem::receive_packets() {
    while (running.load(std::memory_order_acquire)) {
        OrderPacket packet;
        size_t size = sizeof(OrderPacket);
        if (nice.receive_packet(&packet, size)) {
            if (size == sizeof(OrderPacket)) {
                order_queue.enqueue(packet);
            }
        }
    }
}

void TradingSystem::run() {
    running.store(true, std::memory_order_release);
    std::thread process_thread(&TradingSystem::process_orders, this);
    std::thread receive_thread(&TradingSystem::receive_packets, this);

    process_thread.join();
    receive_thread.join();
}

void TradingSystem::stop() {
    running.store(false, std::memory_order_release)
}