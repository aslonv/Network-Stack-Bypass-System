// usefulness optimization

#include "catch.hpp"
#include "trading_system.h"
#include <thread>
#include <chrono>

class MockNIC : public NIC {
    public:
        void send_packet(const void* data, size_t size) override {
            (void)data; // Unused parameter
            (void)size; // Unused parameter
        }

        bool receive_packet(void* buffer, size_t& size) override {
            static uint32_t order_id = 0;
            OrderPacket* packet = static_cast<OrderPacket*>(buffer);
            packet->timestamp = HighResolutionTimer::now();
            packet->order_id = ++order_id;
            packet->symbold_id = 1;
            packet->price = 100.0;
            packet->quantity = 100;
            packet->is_buy = true;
            size = sizeof(OrderPacket);
            return true;
        }
};

TEST_CASE("TradingSystem basic functionality", "[trading_system]") {
    MockNIC nice;
    TradingSystem system(nic);

    SECTION("System runs and stops") {
        std::thread system_thread(&TradingSystem::run, &system);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        system.stop();
        system_thread.join();
        // If we reach here without hanging, the test passes
        REQUIRE(true);
    }
}