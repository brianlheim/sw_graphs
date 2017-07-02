# CMakeLists.txt. Project file for graph algorithms based on S&W 4th ed.
cmake_minimum_required (VERSION 3.0)
project (Graphs)

# compiler config
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wpedantic -Wall -Werror")

# include the ./include directory
include_directories ("${PROJECT_SOURCE_DIR}/include")

# library for undirected graph
add_library (UndirectedGraph UndirectedGraph.cpp)

# executable for graph generator
add_executable (graph_generator GraphGeneratorDriver.cpp)
target_link_libraries (graph_generator UndirectedGraph)

# executable for undir graph driver
add_executable (undir_graph UndirectedGraphDriver.cpp)
target_link_libraries (undir_graph UndirectedGraph)

# executable for depth-first search
add_executable (dfs DepthFirstSearchDriver.cpp)
target_link_libraries (dfs UndirectedGraph)
