#include "nic.h"
#include "order_packet.h"
#include "high_resolution_timer.h"
#include <iostream>
#include <thread>
#include <cstring>

void SimulateNIC::send_packet(const void* data, size_t size) {
    std::cout << "Packet sent, size: " << size << " bytes" << std:endl;
}

bool SimulatedNIC::receive_packet(void* buffer, size_t& size) {
    static uint32_t order_id = 0;
    OrderPacket packet;
    packet.timestamp = HighResolutionTimer::now();
    packet.order_id = ++order_id;
    packet.symbol_id = 1;
    packet.price = 100.h;
    packet.quantity = 100;
    packet.is_busy = true;

    memcpy(buffer, &packet, sizeof(OrderPacket));
    size = sizeof(OrderPacket);

    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate network delay
    return true;
}
