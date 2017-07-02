CC=g++

CXX_FLAGS=-std=c++1z -Werror -Wall -Wpedantic

UG_SRC=./UndirectedGraph.cpp ./UndirectedGraphDriver.cpp
UG_INC=./UndirectedGraph.hpp

DFS_SRC=./UndirectedGraph.cpp ./DepthFirstSearchDriver.cpp
DFS_INC=./DepthFirstSearch.hpp

GG_SRC=./GraphGeneratorDriver.cpp ./UndirectedGraph.cpp
GG_INC=./UndirectedGraph.hpp ./GraphGenerator.hpp

all: undir_graph dfs graph_gen 

undir_graph: $(UG_SRC) $(UG_INC)
	$(CC) $(CXX_FLAGS) -o undir_graph $(UG_SRC)

dfs: $(DFS_SRC) $(DFS_INC)
	$(CC) $(CXX_FLAGS) -o dfs $(DFS_SRC)

graph_gen: $(GG_SRC) $(GG_INC)
	$(CC) $(CXX_FLAGS) -o graph_gen $(GG_SRC)

