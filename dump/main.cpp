#include <iostream>
#include <cstdint>
#include <sys/auxv.h>

int main(int argc, char *argv[])
{
    char* vdso = reinterpret_cast<char*>(getauxval(AT_SYSINFO_EHDR));
    const std::uint32_t page_size = getauxval(AT_PAGESZ);
    std::cout.write(vdso, 2 * page_size);
    return 0;
}
