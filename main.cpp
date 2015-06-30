#include <iostream>

#include <linux/version.h>

typedef uint64_t cycle_t;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint64_t gtod_long_t;
typedef uint32_t seqcount_t;
typedef long time_t;
struct timezone {
    int a;
    int b;
};

#include <linux_clocksource.h>
#include <linux_vgtod.h>
#define __VVAR_KERNEL_LDS
#define EMIT_VVAR(name, offset) \
    static const uint32_t name##_offset = offset;
#include <asm/vvar.h>
#undef __VVAR_KERNEL_LDS

const struct vsyscall_gtod_data *vgtod(void)
{
    static struct vsyscall_gtod_data *gtod = NULL;

    if (!gtod) {
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3, 17, 0)
        char *vdso = (char *)getauxval(AT_SYSINFO_EHDR);
        if (!vdso) {
            return NULL;
        }
        unsigned long page_size = getauxval(AT_PAGESZ);
        /* cf. vvar_start in arch/x86/vdso/vdso-layout.lds.S */
        char *vvar_start = vdso - 2 * page_size;
#else
        /* Even with ASLR in older kernel versions the vvar page is mapped
         * to the same address */
        char *vvar_start = (char *)0xffffffffff5ff000;
#endif
        gtod = (struct vsyscall_gtod_data *)
            (vvar_start + vsyscall_gtod_data_offset);
    }

    return gtod;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3, 15, 0)
#define vclock_mode clock.vclock_mode
#define shift clock.shift
#define mult clock.mult
#define mask clock.mask
#endif

int main(int argc, char *argv[])
{
    const vsyscall_gtod_data* gtod = vgtod();

    if (gtod == nullptr) {
        std::cout << "failed to get gtod pointer\n";
        return -1;
    }
    std::cout << "gtod->vclock_mode: " << gtod->vclock_mode << "\n";
    std::cout << "gtod->shift: " << gtod->shift << "\n";
    std::cout << "gtod->mult: " << gtod->mult << "\n";
    std::cout << "gtod->mask: " << std::hex << gtod->mask << std::dec << "\n";
    std::cout << "\n";

    if (gtod->vclock_mode == VCLOCK_TSC) {
        std::cout << "tsc clock mode\n";
        auto cycle_ns = static_cast<double>(gtod->mult) / (1 << gtod->shift);
        std::cout << "period: " << cycle_ns << " ns" << "\n";
        std::cout << "frequency: " << 1000/cycle_ns << " Mhz" << "\n";
    }
    return 0;
}
