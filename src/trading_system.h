#include "nic.h"
#include "lock_free_queue.h"
#include "order_packet.h"
#include <atomic>

class TradingSystem {
    private:
        NIC& nice;
        LockFreeQueue<OrderPacket, 1024> order_queue;
        std::atomic<bool> running{false};

        void process_orders();
        void receive_packets();
    
    public: 
        explicity TradingSystem(NIC& nic);
        void run();
        void stop();
};

#endif // TRADING_SYSTEM_H