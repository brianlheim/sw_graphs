/** \file GraphGenerator.hpp
 * Generation functions for undirected graph.
 *
 * \author Brian Heim
 * \date   2017-07-02
 */

#pragma once

#include "AbstractUGraph.hpp"

#include <random>
#include <istream>

#include <iostream>

class GraphGenerator
{
public:
  typedef std::uniform_int_distribution<AbstractUGraph::VertexID> int_gen_t;
  typedef AbstractUGraph::size_type size_type;

  /// Constructs a generator using the `graph`.
  /// Duplicate and self-loop edges are turned off.
  GraphGenerator( AbstractUGraph * graph ) :
    _graph(graph),
    _engine(),
    _generator(0, graph->v()-1),
    _allow_duplicate_edges(false),
    _allow_self_loops(false)
  { }

  /// Constructs a generator using the `graph`, adding `num_edges`.
  /// Duplicate and self-loop edges are turned off.
  GraphGenerator( AbstractUGraph * graph, size_type num_edges ) :
    _graph(graph),
    _engine(),
    _generator(0, graph->v()-1),
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
          std::to_string(num_edges+_graph->e()) +
          " were requested."
          );

    for ( size_type i = 0; i < num_edges; ++i )
      addEdge();
  }

  AbstractUGraph const& getGraph() { return *_graph; }

  // Configuration features

  bool allowingDuplicateEdges() const          { return _allow_duplicate_edges; }

  bool allowingSelfLoops() const               { return _allow_self_loops; }

  void allowDuplicateEdges( bool const allow ) { _allow_duplicate_edges = allow; }

  void allowSelfLoops( bool const allow )      { _allow_self_loops = allow; }

protected:

  /// `true` if we can add `num_edges` more edges to the graph
  bool canAddEdges( size_type num_edges ) const
  {
    return _allow_duplicate_edges || ( maxEdges() >= num_edges + _graph->e() );
  }

  /// Returns the maximum number of edges this graph can contain
  size_type maxEdges() const
  {
    size_type const v_count                        = _graph->v();
    size_type const max_edges_between_two_vertices = v_count * (v_count-1) / 2;
    size_type const max_self_loops                 = _allow_self_loops ? v_count : 0;

    return max_edges_between_two_vertices + max_self_loops;
  }

  void addEdge()
  {
    // loop until we successfully add an edge
    while ( true ) {
      AbstractUGraph::VertexID v, w;
      v = _generator(_engine);
      w = _generator(_engine);

      // Check for a self-loop
      if ( _allow_self_loops || v != w ) {

        // Check for an existing edge
        AbstractUGraph::AdjacencyList adj_list = _graph->verticesAdjacentTo(v);
        if ( _allow_duplicate_edges || std::find( adj_list.begin(), adj_list.end(), w ) == adj_list.end() ) {

          // Finally add the edge and exit the loop
          _graph->addEdge( v, w );
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
  std::unique_ptr<AbstractUGraph> _graph; ///< The graph
  std::mt19937_64 _engine;                ///< Random engine
  int_gen_t _generator;                   ///< Uniform int distribution

  bool _allow_duplicate_edges;            ///< Whether or not to allow duplicate edges
  bool _allow_self_loops;                 ///< Whether or not to allow self loops
};

