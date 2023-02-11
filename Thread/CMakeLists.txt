cmake_minimum_required(VERSION 3.20.1)

project(emscripten-thread)

add_executable(side_module_mt ${CMAKE_SOURCE_DIR}/side.cpp)
target_compile_options(side_module_mt PRIVATE -g -pthread -sSIDE_MODULE)
target_link_options(side_module_mt PRIVATE -g -pthread -sSIDE_MODULE)
set_target_properties(
  side_module_mt
  PROPERTIES SUFFIX ".wasm"
             CXX_STANDARD 17
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(test_mt ${CMAKE_SOURCE_DIR}/main.cpp)
target_compile_options(test_mt PRIVATE -g -pthread -sMAIN_MODULE)
target_link_options(test_mt PRIVATE -g -pthread -sPROXY_TO_PTHREAD -sMAIN_MODULE)
set_target_properties(
  test_mt
  PROPERTIES SUFFIX ".html"
             CXX_STANDARD 17
             RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
