# ##############################################################################
# # CMake         # #
# ##############################################################################

# The minimum version of 'cmake' necessary to build this project
cmake_minimum_required(VERSION 3.24)

project(
  CardDB
  LANGUAGES CXX
  VERSION 0.0.1)

include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

include(FetchContent)
FetchContent_Declare(lexy URL https://lexy.foonathan.net/download/lexy-src.zip)
FetchContent_MakeAvailable(lexy)

add_subdirectory(extern/magic_enum EXCLUDE_FROM_ALL)
add_subdirectory(extern/fmt EXCLUDE_FROM_ALL)

add_library(
  CardDB
  INTERFACE
  "include/cubeartisan/carddb/card.hpp"
  "include/cubeartisan/carddb/grammar/utils.hpp"
  "include/cubeartisan/carddb/grammar/values.hpp"
  "include/cubeartisan/carddb/grammar/accessors.hpp")

target_include_directories(CardDB INTERFACE "include")
target_compile_definitions(CardDB INTERFACE LEXY_HAS_NTTP)

target_compile_features(CardDB INTERFACE cxx_std_20)

set_target_properties(
  CardDB
  PROPERTIES CXX_STANDARD 20
             CXX_STANDARD_REQUIRED ON
             CXX_EXTENSIONS OFF)

target_link_libraries(CardDB INTERFACE fmt::fmt foonathan::lexy
                                       magic_enum::magic_enum)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${PROJECT_BINARY_DIR}/CardDBConfigVersion.cmake"
  VERSION 0.0.1
  COMPATIBILITY AnyNewerVersion)
get_filename_component(PREJS ./emscripten/pre.js ABSOLUTE)

message(${CMAKE_SYSTEM_NAME})

if(CMAKE_SYSTEM_NAME STREQUAL "Emscripten")
  add_executable(CardDBWasmWebWorker "src/emscripten.cpp")
  set_target_properties(CardDBWasmWebWorker PROPERTIES SUFFIX ".js")
  target_link_libraries(CardDBWasmWebWorker PUBLIC CardDB)
  target_compile_options(
    CardDBWasmWebWorker
    PUBLIC $<$<CONFIG:Debug>:-gsource-map>
           $<$<CONFIG:RelWithDebInfo>:-gsource-map>
           $<$<CONFIG:RelWithDebInfo>:-flto> $<$<CONFIG:Release>:-flto>)
  target_link_options(
    CardDBWasmWebWorker
    PUBLIC
    --bind
    --no-entry
    --pre-js
    "${PREJS}"
    "-sEVAL_CTORS=1"
    "-sSTRICT=1"
    "-sMALLOC=dlmalloc"
    "-sALLOW_MEMORY_GROWTH=1"
    "-sEXPORT_ES6=1"
    "-sMODULARIZE=1"
    "-sFORCE_FILESYSTEM=0"
    "-sASSERTIONS=1"
    "-sENVIRONMENT=web,worker"
    "-sFILESYSTEM=0"
    $<$<CONFIG:Debug>:-gsource-map>
    $<$<CONFIG:RelWithDebInfo>:-flto>
    $<$<CONFIG:RelWithDebInfo>:-gsource-map>
    $<$<CONFIG:Release>:--closure=1>
    $<$<CONFIG:Release>:-flto>)

  add_executable(CardDBWasmNodeWorker "src/emscripten.cpp")
  set_target_properties(CardDBWasmNodeWorker PROPERTIES SUFFIX ".cjs")
  target_link_libraries(CardDBWasmNodeWorker PUBLIC CardDB)
  target_compile_options(
    CardDBWasmNodeWorker
    PUBLIC $<$<CONFIG:Debug>:-gsource-map>
           $<$<CONFIG:RelWithDebInfo>:-gsource-map>
           $<$<CONFIG:RelWithDebInfo>:-flto> $<$<CONFIG:Release>:-flto>)
  target_link_options(
    CardDBWasmNodeWorker
    PUBLIC
    --bind
    --no-entry
    --pre-js
    "${PREJS}"
    "-sEVAL_CTORS=1"
    "-sSTRICT=1"
    "-sALLOW_MEMORY_GROWTH=1"
    "-sMALLOC=dlmalloc"
    "-sMODULARIZE=1"
    "-sFORCE_FILESYSTEM=0"
    "-sEXPORT_NAME=createCardDB"
    "-sASSERTIONS=1"
    "-sENVIRONMENT=node,worker"
    "-sFILESYSTEM=0"
    $<$<CONFIG:Debug>:-gsource-map>
    $<$<CONFIG:RelWithDebInfo>:-flto>
    $<$<CONFIG:RelWithDebInfo>:-gsource-map>
    $<$<CONFIG:Release>:--closure=1>
    $<$<CONFIG:Release>:-flto>)
else()
  add_executable(CardDBBear "src/test.cpp")
  target_link_libraries(CardDBBear PUBLIC CardDB)
  target_compile_options(CardDBBear PUBLIC $<$<CONFIG:RelWithDebInfo>:-flto>
                                           $<$<CONFIG:Release>:-flto>)
  target_link_options(CardDBBear PUBLIC $<$<CONFIG:RelWithDebInfo>:-flto>
                      $<$<CONFIG:Release>:-flto>)
endif()
