cmake_minimum_required(VERSION 3.16)
project (ship_types)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(guarded_transport_ship)
add_subdirectory(pirate_ship)
add_subdirectory(security_ship)
add_subdirectory(transport_ship)
