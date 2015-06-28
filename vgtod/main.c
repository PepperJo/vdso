#include <stddef.h>
#include <stdint.h>
#include <sys/auxv.h>

#include <vgtod.h>
#define __VVAR_KERNEL_LDS
#define EMIT_VVAR(name, offset) \
    static const uint32_t name##_offset = offset;
#include <asm/vvar.h>
#undef __VVAR_KERNEL_LDS

const struct vsyscall_gtod_data *vgtod(void)
{
    static struct vsyscall_gtod_data *gtod = NULL;

    if (!gtod) {
        char *vdso = (char *)getauxval(AT_SYSINFO_EHDR);
        if (!vdso) {
            return NULL;
        }
        unsigned long page_size = getauxval(AT_PAGESZ);
        /* cf. vvar_start in arch/x86/vdso/vdso-layout.lds.S */
        char *vvar_start = vdso - 2 * page_size;
        gtod = (struct vsyscall_gtod_data *)
            (vvar_start + vsyscall_gtod_data_offset);
    }

    return gtod;
}

