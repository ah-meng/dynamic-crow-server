cmake_minimum_required(VERSION 3.29)
project(dynamic_server)

set(CMAKE_CXX_STANDARD 17)

option(ENABLE_A_ENDPOINT "Enable A endpoint" ON)
option(ENABLE_B_ENDPOINT "Enable B endpoint" ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    set(DEBUG TRUE)
endif ()

add_subdirectory(Common)
add_subdirectory(Util)
add_subdirectory(Service)

if (ENABLE_A_ENDPOINT)
    add_subdirectory(A)
endif ()

if (ENABLE_B_ENDPOINT)
    add_subdirectory(B)
endif ()
