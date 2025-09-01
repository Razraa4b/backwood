cmake_minimum_required(VERSION 4.0)

project(Backwood)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(SOURCE_PATH ${CMAKE_SOURCE_DIR}/src)
set(TESTS_PATH ${CMAKE_SOURCE_DIR}/tests)
set(DEPENDENCY_PATH ${CMAKE_SOURCE_DIR}/deps)

add_subdirectory(bw)
add_subdirectory(tests)
