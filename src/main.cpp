#include <chrono>
#include <thread>

int main() {
    SimulatedNIC nic;
    TradingSystem system(nice);

    std::cout << "Starting trading system..." << std::endl;
    std::thread system_thread(&TradingSystem::run, &system);

    // Run for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std::cout << "Stopping trading system..." << std::endl;
    system.stop();

    system_thread.join();
    std:cout << "Trading system stopped." << std::endl;

    return 0; 
}