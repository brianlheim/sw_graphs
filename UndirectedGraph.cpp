/** \file   UndirectedGraph.cpp
 * Undirected graph implementation.
 * Based on Sedgewick and Wayne, 4th ed.
 *
 * \author Brian Heim
 * \date   2017-06-30
 */

#include "UndirectedGraph.hpp"

#include <istream> // istream
#include <string> // string
#include <sstream> // ostringstream
#include <ios> // streamsize
#include <cmath> // log10

using std::ostringstream;
using std::istream;
using std::vector;
using std::streamsize;
using std::string;

UndirectedGraph::UndirectedGraph( size_type const size ) : _adjacencies(size) { }

UndirectedGraph::UndirectedGraph( istream & in ) : _adjacencies()
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

UndirectedGraph::size_type UndirectedGraph::v() const
{
  return _adjacencies.size();
}

UndirectedGraph::size_type UndirectedGraph::e() const
{
  size_type e = 0;
  for ( auto const& adjacency_list : _adjacencies )
    e += adjacency_list.size();
  return e / 2;
}

UndirectedGraph::AdjacencyList const& UndirectedGraph::verticesAdjacentTo( VertexID const v ) const
{
  return _adjacencies[v];
}

void UndirectedGraph::addEdge( VertexID const v, VertexID const w )
{
  _adjacencies[v].push_back( w );
  _adjacencies[w].push_back( v );
}

string UndirectedGraph::toString() const
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
