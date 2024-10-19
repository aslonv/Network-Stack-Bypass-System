#ifndef NIC_H
#define NIC_H

#include <cstddef>

class NIC {
    public:
        virtual ~NIC() = default;
        virtual void send_packet(const void* data, size_t size) = 0;
        virtual bool receive_packet(void* buffer, size_t& size) = 0; 
};

class SimulatedNIC : public NIC {
    public: 
        void send_packet(const void* data, size_t size) override;
        bool receive_packet(void* buffer, size_t& size) override;
};

#endif // NIC_H