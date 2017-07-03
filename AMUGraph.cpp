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

  read_edges( in, edge_count );
}

/// TODO: don't print self-loops twice
string AMUGraph::toString() const
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

string AMUGraph::toInputString() const
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
