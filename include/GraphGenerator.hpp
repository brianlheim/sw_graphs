/** \file GraphGenerator.hpp
 * Generation functions for undirected graph.
 *
 * \author Brian Heim
 * \date   2017-07-02
 */

#pragma once

#include <random>
#include <istream>

#include <iostream>

template<class G> class GraphGenerator
{
public:
  typedef std::uniform_int_distribution<typename G::VertexID> int_gen_t;
  typedef typename G::size_type size_type;

  /// Creates an unconnected graph with `size` vertices.
  GraphGenerator( size_type size ) :
    _graph(size),
    _engine(),
    _generator(0, size-1),
    _allow_duplicate_edges(false),
    _allow_self_loops(false)
  { }

  /// Constructs a graph with `size` vertices and `num_edges` edges.
  GraphGenerator( size_type size, size_type num_edges ) :
    _graph(size),
    _engine(),
    _generator(0, size-1),
    _allow_duplicate_edges(false),
    _allow_self_loops(false)
  {
    addEdges( num_edges );
  }

  /// Add `num_edges` edges to the graph; throws a domain_error if too many edges are requested.
  void addEdges( size_type num_edges )
  {
    if ( !canAddEdges(num_edges) )
      throw std::domain_error(
          std::string("Graph would be fully connected with ") +
          std::to_string(maxEdges()) +
          " edges, but " +
          std::to_string(num_edges+_graph.e()) +
          " were requested."
          );

    for ( size_type i = 0; i < num_edges; ++i )
      addEdge();
  }

  G const& getGraph() { return _graph; }

  // Configuration features

  bool allowingDuplicateEdges() const { return _allow_duplicate_edges; }

  bool allowingSelfLoops() const { return _allow_self_loops; }

  void allowDuplicateEdges( bool const allow ) { _allow_duplicate_edges = allow; }

  void allowSelfLoops( bool const allow ) { _allow_self_loops = allow; }

protected:

  /// `true` if we can add `num_edges` more edges to the graph
  bool canAddEdges( size_type num_edges ) const
  {
    return _allow_duplicate_edges || ( maxEdges() < num_edges + _graph.e() );
  }

  /// Returns the maximum number of edges this graph can contain
  size_type maxEdges() const
  {
    size_type const max_edges_between_two_vertices = (_graph.v() * (_graph.v()-1)) / 2;
    size_type const max_self_loops                 = _allow_self_loops ? _graph.v() : 0;

    return max_edges_between_two_vertices + max_self_loops;
  }

  void addEdge()
  {
    while ( true ) {
      typename G::VertexID v, w;
      v = _generator(_engine);
      w = _generator(_engine);

      if ( _allow_self_loops || v != w ) {
        typename G::AdjacencyList adj_list = _graph.verticesAdjacentTo(v);
        if ( _allow_duplicate_edges || std::find( adj_list.begin(), adj_list.end(), w ) == adj_list.end() ) {
          _graph.addEdge( v, w );
          break;
        } else {
          std::clog << "Skipping existing edge: (" << v << ", " << w << ")" << std::endl;
        }
      } else {
        std::clog << "Skipping self-loop: (" << v << ", " << w << ")" << std::endl;
      }
    }
  }

private:
  G _graph;                    ///< The graph
  std::mt19937_64 _engine;     ///< Random engine
  int_gen_t _generator;        ///< Uniform int distribution

  bool _allow_duplicate_edges; ///< Whether or not to allow duplicate edges
  bool _allow_self_loops;      ///< Whether or not to allow self loops
};

