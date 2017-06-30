/** \file   UndirectedGraph.hpp
 * Undirected graph implementation.
 * Based on Sedgewick and Wayne, 4th ed.
 *
 * \author Brian Heim
 * \date   2017-06-30
 */

#pragma once

#include <cstddef> // size_t
#include <istream> // istream
#include <vector> // vector

/// Basic undirected graph.
class UndirectedGraph
{
public:
  //--------- Types ----------//

  /// vertex ID type
  typedef size_t VertexID;
  typedef size_t size_type;
  typedef std::vector<VertexID> AdjacencyList;

  //--------- Constructors --------//

  /// size constructor
  UndirectedGraph( size_type const size );

  /// input stream constructor
  UndirectedGraph( std::istream in );

  //--------- Accessors ---------//

  /// Number of vertices
  size_type v() const;

  /// Number of edges
  size_type e() const;

  /// Vertices adjacent to the given vertex
  AdjacencyList const& verticesAdjacentTo( VertexID const v ) const;

  //--------- Mutators ---------//

  /// Creates an edge between the two named vertices.
  /// It is possible to add the same edge twice.
  void addEdge( VertexID const v, VertexID const w );

  //--------- Description ---------//

  /// Returns the graph as a string
  std::string toString() const;

private:

  std::vector<AdjacencyList> _adjacencies;

};
