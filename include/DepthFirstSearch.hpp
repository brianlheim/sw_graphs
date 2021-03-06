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
      _out << indentString(vs.size()) << id << " push\n";

    vs.push( id );
  }

  /// All the bookkeeping needed to get a vertex for processing
  V_ID getNextVisitedVertex( VertexStack& vs ) const
  {
    V_ID ret = vs.top();
    vs.pop();

    // log activity
    if ( _trace )
      _out << indentString(vs.size()) << ret << " pop\n";

    return ret;
  }

  /// Check all the vertices adjacent to the current vertex
  void checkAdjacent( VertexStack& vs, V_ID const id )
  {
    if ( _trace )
      _out << indentString(vs.size()) << "(" << id << ")\n";

    // if the adjacent is marked, ignore it
    // otherwise, mark it and add it to the back of the queue
    if ( !_marks[id] )
      visitVertex( vs, id );
  }

  inline static std::string indentString( size_t count )
  {
    return std::string( count*TAB_SIZE, ' ' );
  }

  std::vector<bool> _marks;

  size_t _count;
  bool _trace;
  std::ostream& _out;

  static const size_t TAB_SIZE = 2;
};
