/** \file DepthFirstSearch.hpp
  * Implements depth-first search on a graph.
  *
  * \author Brian Heim
  * \date   2017-06-30
  */

#pragma once

#include <vector>
#include <stack>
#include <ostream>

template<class G> class DepthFirstSearch
{
public:
  typedef typename G::VertexID V_ID;
  typedef std::stack<V_ID> VertexStack;

  /// Find vertices connected to source vertex `s`
  DepthFirstSearch( G g, V_ID s, bool traceProgress, std::ostream& os ) :
    _marks(g.v(), false),
    _count(0),
    _trace(traceProgress),
    _out(os)
  {
    // create a stack of vertices to explore
    VertexStack vertex_stack;

    // visit the source
    visitVertex( vertex_stack, s );

    while ( !vertex_stack.empty() ) {

      // get the front item off the queue
      const V_ID current_vertex = getNextVisitedVertex( vertex_stack );

      // for each of that vertex's adjacents
      for ( auto const adj_vertex : g.verticesAdjacentTo(current_vertex) )
        checkAdjacent( vertex_stack, adj_vertex );
    }
  }

  /// Is `v` connected to the source vertex?
  bool marked( V_ID v ) const { return _marks[v]; }

  /// How many vertices are connected to the source?
  size_t count() const { return _count; }

private:

  /// ALl bookkeeping needed to remember a vertex for later processing
  void visitVertex( VertexStack& vs, V_ID const id )
  {
    _marks[id] = true;
    ++_count;

    // log activity
    if ( _trace )
      _out << "Pushing " << id << ".\n";

    vs.push( id );
  }

  /// All the bookkeeping needed to get a vertex for processing
  V_ID getNextVisitedVertex( VertexStack& vq ) const
  {
    V_ID ret = vq.top();

    // log activity
    if ( _trace )
      _out << "Popping the stack. Top element is " << ret << ".\n";

    vq.pop();
    return ret;
  }

  /// Check all the vertices adjacent to the current vertex
  void checkAdjacent( VertexStack& vq, V_ID const id )
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
