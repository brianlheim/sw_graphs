/** \file GraphInfo.hpp
  *
  * Various bits of information about a graph which can be
  * discovered via bfs & dfs.
  *
  * \author Brian Heim
  * \date 2017-07-21
  */

#pragma once

#include <vector>
#include <ostream>
#include <queue>
#include <stack>
#include <experimental/optional>
#include <tuple>

namespace GraphInfo {

/** \brief Finds a cycle in a graph if one exists
 *
 * \returns an optional containing a cycle represented as a vector, or nothing
 * if no cycle was found.
 */
template<class G>
std::experimental::optional<std::vector<typename G::VertexID>> findCycle( G const& graph )
{
  typedef typename G::VertexID V_ID;
  typedef std::vector<V_ID> Path;

  // create an array for recording what we've already visited
  std::vector<bool> marks( graph.v(), false );

  // create an array for where each vertex is visited from
  std::vector<V_ID> vertexAncestors( graph.v(), 0 );

  // create a stack for recording the search history
  std::stack<V_ID> vertexStack;

  // a way to tell if we've found a cycle
  bool foundCycle = false;

  // this will be filled with the last cycle link, if there was a cycle
  // the first element will be the vertex currently being searched from.
  // In other words, the ordering is { searchTip, neighbor }. There is
  // and edge from searchTip to neighbor, but we never follow it.
  std::pair<V_ID, V_ID> cycleLink;

  // check each vertex in turn
  for ( V_ID vertex = 0; !foundCycle && vertex < graph.v(); ++vertex ) {
    // short-circuit if we found a cycle and skip if this vertex is marked
    if ( !marks[vertex] && !foundCycle ) {
      marks[vertex] = true;
      vertexAncestors[vertex] = vertex;
      vertexStack.push( vertex );
    } else {
      continue;
    }

    // invariant: we have not yet explored the neighbors of each vertex
    // on the stack.
    while ( !vertexStack.empty() && !foundCycle ) {
      // get the top of the stack
      auto const topVertex = vertexStack.top();
      vertexStack.pop();

      // check each of its neighbors
      for ( auto const neighbor : graph.verticesAdjacentTo(topVertex) ) {

        if ( !marks[neighbor] ) {
          // "visit" by marking, recording ancestor, and pushing to the stack
          marks[neighbor] = true;
          vertexAncestors[neighbor] = topVertex;
          vertexStack.push( neighbor );

        } else if ( vertexAncestors[topVertex] != neighbor ) {
          // record the cycle link and break from the inner loop
          foundCycle = true;
          cycleLink = std::make_pair( topVertex, neighbor );
          break;
        }
      }
    }
  }

  // construct a cycle if we found one
  if ( foundCycle ) {
    // go back from the topVertex (pair.first) to meet the ancestor of the neighbor (pair.second)
    auto commonAncestor = vertexAncestors[cycleLink.second];

    // follow the search tip back to the common ancestor.
    Path cycle;
    for ( auto ce = cycleLink.first; ce != commonAncestor; ce = vertexAncestors[ce] )
      cycle.push_back( ce );

    cycle.push_back( commonAncestor );
    cycle.push_back( cycleLink.second );

    return std::experimental::make_optional( cycle );
  } else {
    return std::experimental::optional<Path>();
  }
}

} // namespace GraphInfo
