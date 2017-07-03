/** \file AMUGraph.cpp
 * Undirected graph implementation using adjacency matrix.
 * Based on Sedgewick and Wayne, 4th ed.
 *
 * \author Brian Heim
 * \date   2017-06-30
 */

#include "AMUGraph.hpp"

#include <istream> // istream
#include <string> // string
#include <sstream> // ostringstream
#include <ios> // streamsize
#include <cmath> // log10

#include <iostream> // debugging

using std::ostringstream;
using std::istream;
using std::vector;
using std::streamsize;
using std::string;

AMUGraph::AMUGraph( istream & in ) : _matrix()
{
  size_type vertex_count, edge_count;
  in >> vertex_count >> edge_count;

  // fill matrix with `false`
  _matrix.resize( vertex_count );
  for ( size_type i = 0; i < vertex_count; ++i )
    _matrix[i].resize( vertex_count, false );

  readEdges( in, edge_count );
}
