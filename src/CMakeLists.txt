# src/CMakeLists.txt
# Project: graphs (S&W 4th ed.)
# Brian Heim, 2017-07-03

# include the header directory
include_directories ( "${PROJECT_SOURCE_DIR}/include" )

# library for undirected graph
add_library ( UGraph ALUGraph.cpp AMUGraph.cpp )

# executable for graph generator
add_executable ( graph_gen GraphGeneratorDriver.cpp )
target_link_libraries ( graph_gen UGraph )
target_link_libraries ( graph_gen ${Boost_LIBRARIES} )

# executable for undir graph driver
add_executable ( undir_graph UGraphDriver.cpp )
target_link_libraries ( undir_graph UGraph )

# executable for depth-first search
add_executable ( dfs DepthFirstSearchDriver.cpp )
target_link_libraries ( dfs UGraph )
target_link_libraries ( dfs ${Boost_LIBRARIES} )

# executable for breadth-first search
add_executable ( bfs BreadthFirstSearchDriver.cpp )
target_link_libraries ( bfs UGraph )
target_link_libraries ( bfs ${Boost_LIBRARIES} )

# executable for connected components
add_executable ( conn_comp ConnectedComponentsDriver.cpp )
target_link_libraries ( conn_comp UGraph )
target_link_libraries ( conn_comp ${Boost_LIBRARIES} )

# executable for graph info's cycle detection
add_executable ( find_cycle FindCycleDriver.cpp )
target_link_libraries ( find_cycle UGraph )
target_link_libraries ( find_cycle ${Boost_LIBRARIES} )

# install files
install ( TARGETS
  graph_gen
  undir_graph
  dfs
  bfs
  conn_comp
  find_cycle

  DESTINATION "${PROJECT_SOURCE_DIR}/bin"
  )
