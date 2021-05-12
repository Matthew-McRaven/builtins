cmake_minimum_required(VERSION 3.10)

# set the project name
project(builtins VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# All files must be specified on the same line, or sources will be reset.
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "pep9/**/reg.cpp" "pep10/**/reg.cpp" "riscv/**/reg.cpp" "src/*.cpp")

add_library (builtins OBJECT ${sources} dependencies/incbin/incbin.c)
target_include_directories(builtins PUBLIC dependencies/incbin "${PROJECT_SOURCE_DIR}/src")

include("dependencies/incbin/IncBinMacro.cmake")
# Read CMake output of this.
move_incbin_to_destination( "${CMAKE_CURRENT_SOURCE_DIR}/pep10" "${CMAKE_CURRENT_BINARY_DIR}/pep10" RECURSE)

enable_testing()
add_subdirectory(test)