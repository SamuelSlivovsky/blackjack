cmake_minimum_required(VERSION 3.18)
project(posZapocet C)

set(CMAKE_C_STANDARD 99)

add_executable(posZapocet main.c krupier.c)
target_link_libraries(posZapocet pthread m)