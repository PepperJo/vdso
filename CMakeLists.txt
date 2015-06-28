cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
project(clock_info)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Werror")

include_directories(${PROJECT_SOURCE_DIR}/vgtod)
find_library(VGTOD_LIBRARY NAMES vgtod PATHS ${PROJECT_SOURCE_DIR}/vgtod)

add_executable(clock_info main.cpp)
target_link_libraries(clock_info ${VGTOD_LIBRARY})
set_property(TARGET clock_info PROPERTY CXX_STANDARD 11)
set_property(TARGET clock_info PROPERTY CXX_STANDARD_REQUIRED ON)
