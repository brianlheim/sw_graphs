/** \file GraphGeneratorDriver.cpp
 * Driver for graph generation.
 *
 * \author Brian Heim
 * \date   2017-07-02
 */

#include "GraphGenerator.hpp"
#include "UndirectedGraph.hpp"

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cin;

int main( int argc, char **argv )
{
  if ( argc < 3 ) {
    cout << "Usage: graph_generator <vertexCount> <edgeCount>" << endl;
    return 1;
  }

  long v_long = std::atol( *++argv );
  long e_long = std::atol( *++argv );
  if ( v_long < 0 || e_long < 0 ) {
    cout << "vertexCount and edgeCount must both be positive" << endl;
    return 2;
  }

  UndirectedGraph::size_type v, e;
  v = (UndirectedGraph::size_type)v_long;
  e = (UndirectedGraph::size_type)e_long;

  GraphGenerator<UndirectedGraph> gen( v, e );
  cout << gen.getGraph().toInputString();
}
