cmake_minimum_required(VERSION 3.18)
project(posSemestralka C)

set(CMAKE_C_STANDARD 99)

add_executable(posSemestralka main.c krupier.c)
target_link_libraries(posSemestralka pthread m)