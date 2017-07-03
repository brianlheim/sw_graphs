# src/CMakeLists.txt
# Project: graphs (S&W 4th ed.)
# Brian Heim, 2017-07-03

# include the header directory
include_directories ("${PROJECT_SOURCE_DIR}/include")

# library for undirected graph
add_library (UGraph ALUGraph.cpp AMUGraph.cpp)

# executable for graph generator
add_executable (graph_gen GraphGeneratorDriver.cpp)
target_link_libraries (graph_gen UGraph)

# executable for undir graph driver
add_executable (undir_graph UGraphDriver.cpp)
target_link_libraries (undir_graph UGraph)

# executable for depth-first search
add_executable (dfs DepthFirstSearchDriver.cpp)
target_link_libraries (dfs UGraph)

# install files
install (TARGETS graph_gen undir_graph dfs DESTINATION "${PROJECT_SOURCE_DIR}/bin")
