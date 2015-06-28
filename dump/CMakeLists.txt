cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Werror")

project(dump_vdso)
add_executable(dump_vdso main.cpp)
set_property(TARGET dump_vdso PROPERTY CXX_STANDARD 11)
set_property(TARGET dump_vdso PROPERTY CXX_STANDARD_REQUIRED ON)
