/** \file DepthFirstSearch.hpp
  * Implements depth-first search on a graph.
  *
  * \author Brian Heim
  * \date   2017-06-30
  */

#pragma once

#include "ALUGraph.hpp"

#include <vector>
#include <stack>

template<class G, class V_ID> class DepthFirstSearch
{
public:

  /// Find vertices connected to source vertex `s`
  DepthFirstSearch( G g, V_ID s ) :
    _marks(g.v(), false),
    _count(0)
  {
    std::stack<V_ID> to_search;
    to_search.push( s );

    // maintain invariants: we've visited _count vertices, and each
    // has been marked as visited.
    _marks[s] = true;
    ++_count;

    while ( !to_search.empty() ) {
      const V_ID id = to_search.top();
      to_search.pop();

      // visit all the unvisited neighbors of the current vertex
      for ( auto const adj_id : g.verticesAdjacentTo(id) ) {
        if ( !_marks[adj_id] ) {
          to_search.push( adj_id );

          // maintain invariants: we've visited _count vertices, and each
          // has been marked as visited.
          _marks[adj_id] = true;
          ++_count;
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
