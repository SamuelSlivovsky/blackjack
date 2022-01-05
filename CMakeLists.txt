cmake_minimum_required(VERSION 3.18)
project(posSemestralka C)

set(CMAKE_C_STANDARD 99)

#add_executable(posSemestralka main.c krupier.c hrac.c hrac.h krupier.h vypisy.c vypisy.h)
add_executable(hrac hrac.c vypisy.c)
add_executable(krupier krupier.c)

target_link_libraries(hrac pthread)
target_link_libraries(krupier pthread)