/** \file GraphGeneratorDriver.cpp
 * Driver for graph generation.
 *
 * \author Brian Heim
 * \date   2017-07-02
 */

#include "GraphGenerator.hpp"
#include "AbstractUGraph.hpp"
#include "ALUGraph.hpp"

#include <boost/program_options.hpp>

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cin;

namespace bpo = boost::program_options;

void parse_program_options( int argc, char **argv, bpo::variables_map& vm )
{
  bpo::options_description desc( "Allowed options" );
  desc.add_options()
    ("help,h"        , "Show this message")
    ("self-loop,s"   , "Allow self-loops in the generated graph")
    ("dupe-edges,d"  , "Allow duplicate edges in the generated graph. Incompatible with -m")
    ("list,l"        , "Use an adjacency list graph implementation. Incompatible with -m")
    ("matrix,m"      , "Use an adjacency matrix graph implementation. Incompatible with -l")

    ("vertex-count,v", bpo::value<AbstractUGraph::size_type>(), "Number of vertices in the graph")
    ("edge-count,e"  , bpo::value<AbstractUGraph::size_type>(), "Number of edges in the graph")
    ;

  // the positional arguments are vertex-count and edge-count
  bpo::positional_options_description pod;
  pod.add( "vertex-count", 1 );
  pod.add( "edge-count", 1 );

  bpo::store(
      bpo::command_line_parser(argc, argv).options(desc).positional(pod).run(),
      vm
      );
  bpo::notify( vm );
}

int main( int argc, char **argv )
{
  bpo::variables_map vm;
  parse_program_options( argc, argv, vm );

  long v_long = std::atol( *++argv );
  long e_long = std::atol( *++argv );
  if ( v_long < 0 || e_long < 0 ) {
    cout << "vertexCount and edgeCount must both be positive" << endl;
    return 2;
  }

  ALUGraph::size_type v, e;
  v = (ALUGraph::size_type)v_long;
  e = (ALUGraph::size_type)e_long;

  GraphGenerator gen( new ALUGraph(v), e );
  cout << gen.getGraph().toInputString();
}
