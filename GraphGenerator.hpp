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
    _generator(0, size-1)
  { }

  /// Constructs a graph with `size` vertices and `num_edges` edges.
  GraphGenerator( size_type size, size_type num_edges ) :
    _graph(size),
    _engine(),
    _generator(0, size-1)
  {
    addEdges( num_edges );
  }

  /// Add `num_edges` edges to the graph; throws a domain_error if too many edges are requested.
  void addEdges( size_type num_edges )
  {
    // protect against infinite loop if the graph is fully connected
    size_type max_edges = (_graph.v() * (_graph.v()+1)) / 2;
    if ( max_edges < num_edges + _graph.e() )
      throw std::domain_error(
          std::string("Graph would be fully connected with ") +
          std::to_string(max_edges) +
          " edges, but " +
          std::to_string(num_edges+_graph.e()) +
          " were requested."
          );

    for ( size_type i = 0; i < num_edges; ++i )
      addEdge();
  }

  G const& getGraph() { return _graph; }

protected:

  void addEdge()
  {
    while ( true ) {
      typename G::VertexID v, w;
      v = _generator(_engine);
      w = _generator(_engine);

      if ( v != w ) {
        typename G::AdjacencyList adj_list = _graph.verticesAdjacentTo(v);
        if ( std::find( adj_list.begin(), adj_list.end(), w ) == adj_list.end() ) {
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
  G _graph; ///< The graph
  std::mt19937_64 _engine; ///< Random engine
  int_gen_t _generator; ///< Uniform int distribution
};
