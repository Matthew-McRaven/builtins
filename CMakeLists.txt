cmake_minimum_required(VERSION 3.10)

# set the project name
project(builtins VERSION 1.0)
find_package( PythonInterp 3.7 REQUIRED )
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Generate the registration code at configure time rather than build time
execute_process(COMMAND ${PYTHON_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/gen/gen.py")

# All files must be specified on the same line, or sources will be reset.
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "pep9/**/reg.cpp" "pep10/**/reg.cpp" "riscv/**/reg.cpp" "src/*.cpp")
set_property(SOURCE ${sources} APPEND PROPERTY  GENERATED)

add_library (builtins OBJECT ${sources})
target_include_directories(builtins PUBLIC "${PROJECT_SOURCE_DIR}/src")

enable_testing()
add_subdirectory(test)