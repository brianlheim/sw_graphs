# Graph Algorithms

C++ implementations of graph algorithms from Sedgewick & Wayne's **Algorithms**, 4th Edition.

To build:

    mkdir build
    cd build
    cmake ..
    cmake --build . --target install

## Executables

    dfs         # depth-first search driver
    bfs         # breadth-first search driver
    conn_comp   # connected components driver
    graph_gen   # graph generator
    undir_graph # undirected graph driver
    find_cycle  # cycle detection

See `--help` on each executable for detailed instructions.

## Dependencies

- boost::program\_options >= 1.63.0
- cmake >= 3.0

If you have [homebrew](https://brew.sh):

    brew install cmake boost

### Specific target dependencies

`find_cycle` requires a compiler with `std::experimental::optional`. This project has been tested
with Apple clang 8.1.0.
