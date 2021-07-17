cmake_minimum_required(VERSION 3.19)
project(Project C)

set(CMAKE_C_STANDARD 99)

add_executable(Project main.c slre.c)
target_link_libraries(Project ws2_32)