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
  ConnectedComponents( G g, bool traceProgress, std::ostream& os );

  /// Returns whether the `source` connected to `target`
  bool connected( V_ID source, V_ID target );

  /// Returns the number of separate components in the graph
  size_type count();

  /// Returns the ID of the given vertex
  size_type id( V_ID vertex );

private:

  std::vector<int> _ids;
  std::ostream& _out;
  size_type _count;
  bool _trace;
};
