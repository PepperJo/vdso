#ifndef VGTOD_H
#define VGTOD_H

#include <stdint.h>

typedef uint64_t cycle_t;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint64_t gtod_long_t;

#include <linux_clocksource.h>
#include <linux_vgtod.h>

#if __cplusplus
extern "C" {
#endif

const struct vsyscall_gtod_data *vgtod(void);

#if __cplusplus
}
#endif
#endif /* VGTOD_H */
