# CMakeLists.txt. Project file for graph algorithms based on S&W 4th ed.
cmake_minimum_required (VERSION 3.0)
project (Graphs)

# compiler config
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wpedantic -Wall -Werror")

# add source subdirectory
add_subdirectory ("${PROJECT_SOURCE_DIR}/src")
