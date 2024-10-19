#ifndef ORDER_PACKET_H
#define ORDER_PACKET_H

#include <cstdint>

struct OrderPacket {
    uint64_t timestamp;
    uint32_t order_id;
    uint32_t symbol_id;
    double price;
    uint32_t quantity;
    bool is_buy;
} __attribute__((packed));

#endif // ORDER_PACKET_H