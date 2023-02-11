cmake_minimum_required(VERSION 3.20.1)

project(emscripten-no-thread)

add_executable(side_module ${CMAKE_SOURCE_DIR}/side.cpp)
target_compile_options(side_module PRIVATE -g -sSIDE_MODULE)
target_link_options(side_module PRIVATE -g -sSIDE_MODULE)
set_target_properties(
  side_module
  PROPERTIES SUFFIX ".wasm"
             CXX_STANDARD 17
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test ${CMAKE_SOURCE_DIR}/main.cpp)
target_compile_options(test PRIVATE -g -sMAIN_MODULE)
target_link_options(test PRIVATE -g -sPROXY_TO_WORKER -sMAIN_MODULE)
set_target_properties(
  test
  PROPERTIES SUFFIX ".html"
             CXX_STANDARD 17
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
