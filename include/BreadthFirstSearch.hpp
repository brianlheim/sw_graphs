/** \file BreadthFirstSearch.hpp
  * Implements breadth-first search on a graph.
  *
  * \author Brian Heim
  * \date   2017-07-04
  */

#pragma once

#include <vector>
#include <queue>

template<class G, class V_ID> class BreadthFirstSearch
{
public:

  /// Find vertices connected to source vertex `s`
  BreadthFirstSearch( G g, V_ID s ) :
    _marks(g.v(), false),
    _count(0)
  {
    // create a queue of vertices to explore
    std::queue<V_ID> vertex_queue;

    // mark the source (updating the counter)
    _marks[s] = true;
    ++_count;

    // add the source to the back of the queue
    vertex_queue.push( s );

    while ( !vertex_queue.empty() ) {

      // get the front item off the queue
      V_ID current_vertex = vertex_queue.front();
      vertex_queue.pop();

      // for each of that vertex's adjacents
      for ( auto const adj_vertex : g.verticesAdjacentTo(current_vertex) ) {

        // if the adjacent is marked, ignore it
        // otherwise, mark it and add it to the back of the queue
        if ( !_marks[adj_vertex] ) {
          _marks[adj_vertex] = true;
          ++_count;
          vertex_queue.push( adj_vertex );
        }
      }
    }
  }

  /// Is `v` connected to the source vertex?
  bool marked( V_ID v ) const { return _marks[v]; }

  /// How many vertices are connected to the source?
  size_t count() const { return _count; }

private:

  std::vector<bool> _marks;

  size_t _count;

};
