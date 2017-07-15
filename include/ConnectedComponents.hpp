/** \file ConnectedComponents.hpp
  *
  * Takes a graph and computes connected components.
  *
  * \author Brian Heim
  * \date 2017-07-14
  */

#pragma once

#include <vector>
#include <ostream>

template<class G> class ConnectedComponents
{
public:
  typedef typename G::VertexID V_ID;
  typedef typename G::size_type size_type;

  /// Find the connected components of the graph
  ConnectedComponents( G g, bool traceProgress, std::ostream& os ) :
    _marks(g.v(), false),
    _ids(g.v(), 0),
    _count(0),
    _trace(traceProgress),
    _out(os)
  {
    for ( V_ID source = 0; source < g.v(); ++source ) {
      if ( !_marks[source] ) {
        depthFirstSearch( g, source );
        ++_count;
      }
    }
  }

  /// Returns whether the `source` connected to `target`
  bool connected( V_ID source, V_ID target ) { return _ids[source] == _ids[target]; }

  /// Returns the number of separate components in the graph
  size_type count() { return _count; }

  /// Returns the ID of the given vertex
  size_type id( V_ID vertex ) { return _ids[vertex]; }

private:

  /// Basic depth first search that marks vertices with visits and component IDs
  void depthFirstSearch( G& g, V_ID source )
  {
    _marks[source] = true;
    _ids[source] = _count;
    for ( auto const& vertex : g.verticesAdjacentTo(source) )
      if ( !_marks[source] )
        dfs( g, source );
  }

  std::vector<bool> _marks;
  std::vector<int> _ids;
  std::ostream& _out;
  size_type _count;
  bool _trace;
};
