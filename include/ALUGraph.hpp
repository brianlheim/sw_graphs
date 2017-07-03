/** \file ALUGraph.hpp
 * Undirected graph implementation using adjacency list.
 * Based on Sedgewick and Wayne, 4th ed.
 *
 * \author Brian Heim
 * \date   2017-06-30
 */

#pragma once

#include "AbstractUGraph.hpp"

#include <cstddef> // size_t
#include <istream> // istream
#include <vector> // vector
#include <ostream> // ostream

/// Basic undirected graph using an adjacency list.
class ALUGraph : public AbstractUGraph
{
public:
  //--------- Constructors --------//

  /// size constructor
  ALUGraph( size_type const size ) : _adjacencies(size) { }

  /// input stream constructor
  ALUGraph( std::istream & in );

  //--------- Accessors ---------//

  /// Number of vertices
  size_type v() const { return _adjacencies.size(); }

  /// Number of edges
  size_type e() const
  {
    size_type e = 0;
    for ( auto const& adjacency_list : _adjacencies )
      e += adjacency_list.size();
    return e / 2;
  }

  /// Vertices adjacent to the given vertex
  AdjacencyList verticesAdjacentTo( VertexID const v ) const { return _adjacencies[v]; }

  //--------- Mutators ---------//

  /// Creates an edge between the two named vertices.
  /// It is possible to add the same edge twice.
  void addEdge( VertexID const v, VertexID const w )
  {
    _adjacencies[v].push_back( w );
    _adjacencies[w].push_back( v );
  }

  //--------- Description ---------//

  /// Returns the graph as a string
  std::string toString() const;

  /// Returns the graph as a string that can be read by the constructor
  std::string toInputString() const;

private:

  std::vector<AdjacencyList> _adjacencies;

};

/// Output stream operator
inline std::ostream& operator<<( std::ostream& os, ALUGraph const& graph )
{
  os << graph.toString();
  return os;
}
