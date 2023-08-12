cmake_minimum_required(VERSION 3.24)

project(graph-generation)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

set(PUB_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

if (DUMP)
    add_definitions(-DDUMP)
endif()

add_subdirectory(lib)
add_subdirectory(tools)
