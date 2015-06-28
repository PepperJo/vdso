cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Werror")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

execute_process(COMMAND uname -r OUTPUT_VARIABLE kv)
string(LENGTH ${kv} len)
math(EXPR len "${len} - 1")
string(SUBSTRING ${kv} 0 ${len} kv)
include_directories(/lib/modules/${kv}/build/arch/x86/include)

execute_process(COMMAND grep -Pzo "struct vsyscall_gtod_data.*?{[^\}]*};"
    /lib/modules/${kv}/build/arch/x86/include/asm/vgtod.h
    OUTPUT_FILE linux_vgtod.h)
execute_process(COMMAND grep "VCLOCK"
    /lib/modules/${kv}/build/arch/x86/include/asm/clocksource.h
    OUTPUT_FILE linux_clocksource.h)

project(vgtod)
add_library(vgtod SHARED main.c)

