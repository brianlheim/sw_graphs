/** \file ALUGraph.cpp
 * Undirected graph implementation.
 * Based on Sedgewick and Wayne, 4th ed.
 *
 * \author Brian Heim
 * \date   2017-06-30
 */

#include "ALUGraph.hpp"

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

ALUGraph::ALUGraph( istream & in ) : _adjacencies()
{
  size_type vertex_count, edge_count;
  in >> vertex_count >> edge_count;

  _adjacencies.resize( vertex_count );
  readEdges( in, edge_count );
}
