cmake_minimum_required(VERSION 3.25)

project(tiny-kv-server LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 14)
    message(FATAL_ERROR "GCC 14+ required (found ${CMAKE_CXX_COMPILER_VERSION})")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 18)
    message(FATAL_ERROR "Clang 18+ required (found ${CMAKE_CXX_COMPILER_VERSION})")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# For clangd / IDE tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

option(KV_BUILD_TESTS "Build the unit tests" ON)
set(KV_SANITIZERS "" CACHE STRING "Comma-separated -fsanitize= list, e.g. address,undefined or thread")

# Applied globally so everything linked into a binary (including test deps) is instrumented
if(KV_SANITIZERS)
    add_compile_options(-fsanitize=${KV_SANITIZERS} -fno-omit-frame-pointer -fno-sanitize-recover=all)
    add_link_options(-fsanitize=${KV_SANITIZERS})
endif()

# Shared warning flags for all project targets
add_library(kv_warnings INTERFACE)
target_compile_options(kv_warnings INTERFACE
    -Wall -Wextra -Wpedantic -Wshadow -Wconversion
)

add_library(kvcore src/core/unique_fd.cpp)
target_include_directories(kvcore PUBLIC src)

add_executable(kvserver src/kvserver/main.cpp)
target_link_libraries(kvserver PRIVATE kv_warnings)

add_executable(kvbench src/kvbench/main.cpp)
target_link_libraries(kvbench PRIVATE kv_warnings)

add_executable(kvtop src/kvtop/main.cpp)
target_link_libraries(kvtop PRIVATE kv_warnings)

if(KV_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
