#include <iostream>
#include <cmath>
#include <cstdint>
#include <limits>

#include <vgtod.h>

static inline std::uint64_t rdtsc()
{
    std::uint32_t lo, hi;
    asm volatile ("lfence; rdtsc" : "=a"(lo), "=d"(hi));
    return lo | (static_cast<std::uint64_t>(hi)
            << std::numeric_limits<decltype(hi)>::digits);
}

int main(int argc, char *argv[])
{
    const vsyscall_gtod_data* gtod = vgtod();

    std::cout << "gtod->vclock_mode: " << gtod->vclock_mode << std::endl;
    std::cout << "gtod->shift: " << gtod->shift << std::endl;
    std::cout << "gtod->mult: " << gtod->mult << std::endl;
    std::cout << "gtod->mask: " << std::hex << gtod->mask << std::dec << std::endl;
    std::cout << "\n";

    if (gtod->vclock_mode == VCLOCK_TSC) {
        auto cycle_ns = static_cast<double>(gtod->mult) / (1 << gtod->shift);
        std::cout << "cycle period: " << cycle_ns << " ns" << std::endl;
        std::cout << "frequency: " << 1000/cycle_ns << " Mhz" << std::endl;
    }
    return 0;
}