/** \file AMUGraph.hpp
 * Undirected graph implementation using adjacency matrix.
 * Based on Sedgewick and Wayne, 4th ed.
 *
 * \author Brian Heim
 * \date   2017-07-02
 */

#pragma once

#include "AbstractUGraph.hpp"

#include <cstddef> // size_t
#include <istream> // istream
#include <vector> // vector
#include <ostream> // ostream

/// Basic undirected graph using an adjacency matrix.
class AMUGraph : public AbstractUGraph
{
public:
  //--------- Constructors --------//

  /// size constructor
  AMUGraph( size_type const size ) : _matrix(size, std::vector<bool>(size)) { }

  /// input stream constructor
  AMUGraph( std::istream & in );

  //--------- Accessors ---------//

  /// Number of vertices
  size_type v() const { return _matrix.size(); }

  /// Number of edges
  size_type e() const
  {
    size_type edge_count = 0;
    for ( size_type row = 0; row < v(); ++row )
      edge_count += std::count( _matrix[row].begin() + row, _matrix[row].end(), true );
    return edge_count;
  }

  /// Vertices adjacent to the given vertex
  AdjacencyList verticesAdjacentTo( VertexID const v ) const
  {
    AdjacencyList adj_list;
    typedef std::vector<bool>::const_iterator citer;
    for ( citer it = _matrix[v].begin(); it != _matrix[v].end(); ++it )
      if ( *it )
        adj_list.push_back( it-_matrix[v].begin() );
    return adj_list;
  }

  /// Degree of vertex `v`; a self-loop is counted twice.
  virtual size_type degree( VertexID const v ) const
  {
    return std::count( _matrix[v].begin(), _matrix[v].end(), true ) + (_matrix[v][v] ? 1 : 0);
  }

  //--------- Mutators ---------//

  /// Creates an edge between the two named vertices.
  /// It is possible to add the same edge twice.
  void addEdge( VertexID const v, VertexID const w )
  {
    _matrix[v][w] = _matrix[w][v] = true;
  }

private:

  typedef std::vector<std::vector<bool>> AdjacencyMatrix;
  AdjacencyMatrix _matrix;

};

/// Output stream operator
inline std::ostream& operator<<( std::ostream& os, AMUGraph const& graph )
{
  os << graph.toString();
  return os;
}
