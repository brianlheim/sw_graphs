/** \file DepthFirstSearch.cpp
 * Driver for DepthFirstSearch
 *
 * \author Brian Heim
 * \date   2017-06-30
 */

#include "ALUGraph.hpp"
#include "DepthFirstSearch.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

using VertexID = UndirectedGraph::VertexID;

int main()
{
  cout << "Driver for depth first search on undirected graph" << endl;
  cout << "Enter the graph:" << endl;

  UndirectedGraph ug = UndirectedGraph( cin );

  cout << "The graph is this: " << endl;
  cout << ug.toString();

  VertexID v_id;
  while (true) {
    cout << "Enter the vertex to search with, or a non-number to quit: ";
    cin >> v_id;
    if ( !cin )
      break;

    DepthFirstSearch<UndirectedGraph, VertexID> dfs( ug, v_id );

    cout << "There are " << dfs.count() << " vertices connected to " << v_id << endl;
  }

  return 0;
}
