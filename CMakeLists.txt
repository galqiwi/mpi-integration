cmake_minimum_required(VERSION 3.20)
project(main)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(main
        crunching.cpp
        crunching.h
        main.cpp
        range.cpp
        range.h
        result.h
        utils.cpp
        utils.h)

target_link_libraries(main ${MPI_LIBRARIES})
