/** \file BreadthFirstSearch.hpp
  * Implements breadth-first search on a graph.
  *
  * \author Brian Heim
  * \date   2017-07-04
  */

#pragma once

#include <vector>
#include <queue>
#include <iostream>

template<class G> class BreadthFirstSearch
{
public:
  typedef typename G::VertexID V_ID;
  typedef std::queue<V_ID> VertexQueue;

  /// Find vertices connected to source vertex `s`
  BreadthFirstSearch( G g, V_ID s ) :
    _marks(g.v(), false),
    _count(0),
    _trace(true),
    _out(std::cout)
  {
    // create a queue of vertices to explore
    VertexQueue vertex_queue;

    // add the source to the back of the queue
    visitVertex( vertex_queue, s );

    while ( !vertex_queue.empty() ) {

      // get the front item off the queue
      V_ID current_vertex = getNextVisitedVertex( vertex_queue );

      // for each of that vertex's adjacents
      for ( auto const adj_vertex : g.verticesAdjacentTo(current_vertex) )
        checkAdjacent( vertex_queue, adj_vertex );
    }
  }

  /// Is `v` connected to the source vertex?
  bool marked( V_ID v ) const { return _marks[v]; }

  /// How many vertices are connected to the source?
  size_t count() const { return _count; }

private:

  /// All the bookkeeping needed to remember a vertex for later processing
  void visitVertex( VertexQueue& vq, V_ID const id )
  {
    // mark the source (updating the counter)
    _marks[id] = true;
    ++_count;

    // log activity
    if ( _trace )
      _out << "Pushing " << id << ".\n";

    vq.push( id );
  }

  /// All the bookkeeping needed to get a vertex for processing
  V_ID getNextVisitedVertex( VertexQueue& vq ) const
  {
    V_ID ret = vq.front();

    // log activity
    if ( _trace )
      _out << "Popping the queue. Front element is " << ret << ".\n";

    vq.pop();
    return ret;
  }

  /// Check all the vertices adjacent to the current vertex
  void checkAdjacent( VertexQueue& vq, V_ID const id )
  {
    if ( _trace )
      _out << "Checking adjacent " << id << ".\n";

    // if the adjacent is marked, ignore it
    // otherwise, mark it and add it to the back of the queue
    if ( !_marks[id] )
      visitVertex( vq, id );
    else if ( _trace )
      _out << "Already marked.\n";
  }

  std::vector<bool> _marks;

  size_t _count;
  bool _trace;
  std::ostream& _out;

};
