cmake_minimum_required(VERSION 3.20.1)

project(emscripten)

add_subdirectory(${CMAKE_SOURCE_DIR}/NoThread)
add_subdirectory(${CMAKE_SOURCE_DIR}/Thread)
