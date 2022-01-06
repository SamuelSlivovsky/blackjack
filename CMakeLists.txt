cmake_minimum_required(VERSION 3.18)
project(posSemestralka C)

set(CMAKE_C_STANDARD 99)

add_executable(hrac hrac.c vypisy.c)
add_executable(krupier krupier.c vypisy.c)


target_link_libraries(hrac pthread)
target_link_libraries(krupier pthread)