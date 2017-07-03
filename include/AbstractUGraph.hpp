/** \file AbstractUGraph.hpp
 * Abstract undirected graph type definition.
 * Based on Sedgewick and Wayne, 4th ed.
 *
 * \author Brian Heim
 * \date   2017-07-02
 */

#pragma once

#include <cstddef> // size_t
#include <istream> // istream
#include <vector> // vector

/// Abstract, basic undirected graph.
class AbstractUGraph
{
public:
  //--------- Types ----------//

  /// vertex ID type
  typedef size_t VertexID;
  typedef size_t size_type;
  typedef std::vector<VertexID> AdjacencyList;

  //--------- Constructors --------//

  /// default constructor
  AbstractUGraph() { }

  //--------- Destructor ---------//

  virtual ~AbstractUGraph() { }

  //--------- Accessors ---------//

  /// Number of vertices
  virtual size_type v() const = 0;

  /// Number of edges
  virtual size_type e() const = 0;

  /// Vertices adjacent to the given vertex
  virtual AdjacencyList verticesAdjacentTo( VertexID const v ) const = 0;

  //--------- Mutators ---------//

  /// Creates an edge between the two named vertices.
  /// It is possible to add the same edge twice.
  virtual void addEdge( VertexID const v, VertexID const w ) = 0;

  //--------- Description ---------//

  /// Returns the graph as a string
  virtual std::string toString() const = 0;

  /// Returns the graph as a string that can be read by the constructor
  virtual std::string toInputString() const = 0;

protected:

  /// Read in `edge_count` edges
  void read_edges( std::istream& in, size_type edge_count )
  {
    for ( size_type i = 0; i < edge_count; ++i ) {
      VertexID v, w;
      in >> v >> w;
      addEdge( v, w );
    }
  }

};
