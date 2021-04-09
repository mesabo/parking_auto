cmake_minimum_required(VERSION 3.17)
project(parkingautoto C)

set(CMAKE_C_STANDARD 99)

add_executable(parkingautoto main.c)
target_link_libraries(parkingautoto mysqlclient)
