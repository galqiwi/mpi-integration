cmake_minimum_required(VERSION 3.20)
project(main)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

set(CMAKE_CXX_COMPILER "mpic++")
set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(main
        src/crunching.cpp
        src/crunching.h
        src/main.cpp
        src/range.cpp
        src/range.h
        src/result.h
        src/utils.cpp
        src/utils.h)

target_link_libraries(main ${MPI_LIBRARIES})
