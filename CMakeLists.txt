cmake_minimum_required(VERSION 3.19.2)
project(robot)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(TEST ON)
set(VERSION 0.0.1)

add_definitions(-std=c++11)

add_subdirectory(src)