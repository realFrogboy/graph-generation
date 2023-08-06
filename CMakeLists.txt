cmake_minimum_required(VERSION 3.24)

project(graph-generation)

if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
endif()

if (DUMP)
    add_definitions(-DDUMP)
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set (COMPILER_SETTINGS -g -Wall -Wextra -Wpedantic)
else ()
    set (COMPILER_SETTINGS -O2 -Wall -Wextra -Wpedantic)
endif ()
add_compile_options(${COMPILER_SETTINGS})

set (SOURCES lib/main.cpp lib/NodeTy.cpp lib/ReducibleGraphTy.cpp lib/DominanceTreeTy.cpp lib/DJGraphTy.cpp lib/GraphDumpTy.cpp lib/DominanceFrontierTy.cpp)

add_executable (${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
