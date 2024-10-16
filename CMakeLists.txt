cmake_minimum_required(VERSION 3.20.1)
project(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_CXX_STANDARD 17)

option(DYN_LINK "Build with dynamic linking" OFF)
option(BUILD_DEBUG "Debug" OFF)
option(SPLIT_MODULE "Split module" OFF)
option(ENABLE_THREADS "Enable threads" OFF)

set(DYN_LINK_TYPE "runtime")
set(OUT_EXT ".js")

set(EMSCRIPTEN_OPTIONS -fwasm-exceptions -g -fsanitize=address,undefined)
if(ENABLE_THREADS)
  set(EMSCRIPTEN_OPTIONS ${EMSCRIPTEN_OPTIONS} -pthread)
endif()
if(BUILD_DEBUG)
  set(EMSCRIPTEN_OPTIONS ${EMSCRIPTEN_OPTIONS} -g)
endif()

set(EMSCRIPTEN_COMPILE_OPTIONS)

set(EMSCRIPTEN_LINK_OPTIONS
    --emit-symbol-map
    -sEXCEPTION_STACK_TRACES=1
    -sFORCE_FILESYSTEM=1 # So that Module.preInit doesn't throw in static linking build
    -sALLOW_MEMORY_GROWTH
    -sNO_EXIT_RUNTIME
)
if(ENABLE_THREADS)
  set(EMSCRIPTEN_LINK_OPTIONS ${EMSCRIPTEN_LINK_OPTIONS} -sPROXY_TO_PTHREAD=1)
endif()
if(SPLIT_MODULE)
  set(EMSCRIPTEN_LINK_OPTIONS ${EMSCRIPTEN_LINK_OPTIONS} -sSPLIT_MODULE=1)
endif()

set(COMPILE_OPTIONS ${EMSCRIPTEN_OPTIONS} ${EMSCRIPTEN_COMPILE_OPTIONS})
set(LINK_OPTIONS ${EMSCRIPTEN_OPTIONS} ${EMSCRIPTEN_LINK_OPTIONS})

if(DYN_LINK)
  add_executable(side-module ${CMAKE_SOURCE_DIR}/c.cpp)
  target_include_directories(side-module PRIVATE ${CMAKE_SOURCE_DIR})
  target_compile_options(side-module PRIVATE ${COMPILE_OPTIONS} -sSIDE_MODULE=2)
  target_link_options(side-module PRIVATE ${LINK_OPTIONS} -sSIDE_MODULE=2
                      -sEXPORTED_FUNCTIONS=_fun4)
  set_target_properties(side-module PROPERTIES SUFFIX ".wasm")
endif()

set(SRC ${CMAKE_SOURCE_DIR}/a.cpp ${CMAKE_SOURCE_DIR}/b.cpp)
if(NOT DYN_LINK)
  set(SRC ${SRC} ${CMAKE_SOURCE_DIR}/c.cpp)
endif()
add_executable(test ${SRC})
target_include_directories(test PRIVATE ${CMAKE_SOURCE_DIR})

if(DYN_LINK)
  set(COMPILE_OPTIONS ${COMPILE_OPTIONS} -sMAIN_MODULE=2)
  set(LINK_OPTIONS ${LINK_OPTIONS} -sMAIN_MODULE=2)
  set(MAIN_MODULE_EXPORTED_FUNCTIONS _pmodule _smodule _main)
  if(DYN_LINK_TYPE STREQUAL "loadtime")
    set(LINK_OPTIONS ${LINK_OPTIONS} ${CMAKE_BINARY_DIR}/side-module.wasm)
    target_compile_definitions(test PRIVATE DYN_LINK_LOADTIME)
  else()
    target_compile_definitions(test PRIVATE DYN_LINK_RUNTIME)
    set(MAIN_MODULE_EXPORTED_FUNCTIONS
        ${MAIN_MODULE_EXPORTED_FUNCTIONS} __ZTIPKc ___cxa_allocate_exception
        ___cxa_throw _iprintf)
  endif()
  if(SPLIT_MODULE)
    set(LINK_OPTIONS ${LINK_OPTIONS} -sINITIAL_TABLE=700)
    set(MAIN_MODULE_EXPORTED_FUNCTIONS ${MAIN_MODULE_EXPORTED_FUNCTIONS} _malloc
      _free)
  endif()
  add_dependencies(test side-module)
  list(JOIN MAIN_MODULE_EXPORTED_FUNCTIONS "," MAIN_MODULE_EXPORTED_FUNCTIONS)
  set(LINK_OPTIONS ${LINK_OPTIONS}
  -sEXPORTED_FUNCTIONS=${MAIN_MODULE_EXPORTED_FUNCTIONS})
endif()

target_compile_options(test PRIVATE ${COMPILE_OPTIONS})
target_link_options(test PRIVATE ${LINK_OPTIONS})
set_target_properties(test PROPERTIES SUFFIX ${OUT_EXT})
em_link_pre_js(test ${CMAKE_SOURCE_DIR}/prejs.js)
