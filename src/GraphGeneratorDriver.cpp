/** \file GraphGeneratorDriver.cpp
 * Driver for graph generation.
 *
 * \author Brian Heim
 * \date   2017-07-02
 */

#include "GraphGenerator.hpp"
#include "AbstractUGraph.hpp"
#include "ALUGraph.hpp"
#include "AMUGraph.hpp"

#include <boost/program_options.hpp>

#include <iostream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::cin;

namespace bpo = boost::program_options;

void parse_program_options( int argc, char **argv, bpo::options_description& desc, bpo::variables_map& vm )
{
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
  using size_type = AbstractUGraph::size_type;

  bpo::options_description desc( "Allowed options" );
  bpo::variables_map vm;
  parse_program_options( argc, argv, desc, vm );

  // if help is requested, just print help and exit
  if ( vm.count("help") ) {
    cout << desc << endl;
    std::exit(EXIT_SUCCESS);
  }

  // check for incompatible options
  if ( vm.count("dupe-edges") && vm.count("matrix") ) {
    cout << "*** Can't use duplicate edges with matrix implementation" << endl;
    std::exit(EXIT_FAILURE);
  }

  if ( vm.count("matrix") && vm.count("list") ) {
    cout << "*** Only one of matrix or list may be requested" << endl;
    std::exit(EXIT_FAILURE);
  }

  size_type v = vm["vertex-count"].as<size_type>();
  size_type e = vm["edge-count"].as<size_type>();

  AbstractUGraph * gptr;
  if ( vm.count("list") )
    gptr = new ALUGraph(v);
  else
    gptr = new AMUGraph(v);

  GraphGenerator gen( gptr );
  gen.allowSelfLoops( vm.count("self-loop") );
  gen.allowDuplicateEdges( vm.count("dupe-edges") );
  gen.addEdges( e );

  cout << gen.getGraph().toInputString();
}
