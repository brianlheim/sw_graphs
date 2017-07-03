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
  for ( size_type i = 0; i < edge_count; ++i ) {
    VertexID v, w;
    in >> v >> w;
    addEdge( v, w );
  }
}

/// TODO: don't print self-loops twice
string ALUGraph::toString() const
{
  ostringstream ss;
  // ss << v() << '\n' << e() << '\n';
  streamsize vertex_field_width = (int)std::ceil(std::log10(v()));
  for ( size_type i = 0; i < v(); ++i ) {
    ss.width( vertex_field_width );
    ss << i << " |";
    for ( auto const& vertex : verticesAdjacentTo(i) ) {
      ss << ' ' << vertex;
    }
    ss << '\n';
  }

  return ss.str();
}

string ALUGraph::toInputString() const
{
  ostringstream ss;
  ss << v() << '\n' << e() << '\n';
  for ( size_type i = 0; i < v(); ++i ) {
    bool seen_self_loop = false;
    for ( auto const& vertex : verticesAdjacentTo(i) ) {
      if ( vertex == i ) {
        if ( seen_self_loop )
          ss << i << ' ' << vertex << '\n';
        seen_self_loop = !seen_self_loop;
      } else if ( vertex > i ) {
        ss << i << ' ' << vertex << '\n';
      }
    }
  }

  return ss.str();
}
