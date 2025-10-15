cmake_minimum_required(VERSION 3.16)
project(AccessibleChess LANGUAGES CXX)

# C++ standard & warnings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
  add_compile_options(/W4 /permissive- /Zc:__cplusplus /EHsc /wd4996)
  # Treat warnings as errors in CI 
  if (DEFINED ENV{CI})
    add_compile_options(/WX)
  endif()
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
  if (DEFINED ENV{CI})
    add_compile_options(-Werror)
  endif()
endif()

# Sources
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
add_executable(chess ${SRC_FILES})
target_include_directories(chess PRIVATE include)

# Enable LTO in Release
include(CheckIPOSupported)
check_ipo_supported(RESULT hasLTO OUTPUT out)
if (hasLTO)
  set_property(TARGET chess PROPERTY INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
endif()

# Tests via doctest
option(ENABLE_TESTS "Build tests" ON)
if (ENABLE_TESTS)
  # Get all source files except main.cpp for tests
  file(GLOB_RECURSE TEST_SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
  list(FILTER TEST_SRC_FILES EXCLUDE REGEX ".*main\\.cpp$")

  add_executable(chess_tests tests/main.cpp ${TEST_SRC_FILES})
  target_include_directories(chess_tests PRIVATE include tests)
  if (NOT MSVC)
    target_compile_options(chess_tests PRIVATE -Wno-unused-parameter)
  endif()
  add_test(NAME chess_tests COMMAND chess_tests)
  include(CTest)
endif()
