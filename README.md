# Graph Algorithms

C++ implementations of graph algorithms from Sedgewick & Wayne's **Algorithms**, 4th Edition.

To build:

    mkdir build
    cd build
    cmake ..
    cmake --build . --target install

## Executables

    dfs # depth-first search driver
    bfs # breadth-first search driver
    conn_comp # connected components driver
    graph_gen # graph generator
    undir_graph # undirected graph driver

See `--help` on each executable for detailed instructions.
  
## Dependencies

- Boost program\_options library >= 1.63.0
- CMake >= 3.0
