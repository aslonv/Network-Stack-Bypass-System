#ifndef HIGH_RESOLUTION_TIMER_H
#define HIGH_RESOLUTION_TIMER_H

#include <cstdint>

class HighResolutionTimer {
    public:
        static uint64_t now() {
            unsigned int lo, hi;
            __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
            return ((uint64_t)hi << 32) | lo;
        }
};

#endif // HIGH_RESOLUTION_TIMER_h