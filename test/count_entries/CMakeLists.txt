cmake_minimum_required(VERSION 3.13)

# set the project name
project(count_entries VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(count_entries main.cpp)
# Allow version header to be included
target_link_libraries(count_entries builtins)
add_test (NAME count_entries COMMAND count_entries)