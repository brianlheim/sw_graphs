/** \file DepthFirstSearch.cpp
 * Driver for DepthFirstSearch
 *
 * \author Brian Heim
 * \date   2017-06-30
 */

#include "AbstractUGraph.hpp"
#include "AMUGraph.hpp"
#include "ALUGraph.hpp"
#include "DepthFirstSearch.hpp"

#include <boost/program_options.hpp>

#include <iostream>
#include <fstream> // ifstream
#include <string> // string

using std::string;
using std::ifstream;
using std::cin;
using std::cout;
using std::endl;

using VertexID = AbstractUGraph::VertexID;
namespace bpo = boost::program_options;

void parse_program_options( int argc, char **argv, bpo::options_description& desc, bpo::variables_map& vm )
{
  desc.add_options()
    ("help,h"      , "Show this message")
    ("input-file,i", "Input file to read")
    ;

  // the positional argument is input-file
  bpo::positional_options_description pod;
  pod.add( "input-file", 1 );

  bpo::store(
      bpo::command_line_parser(argc, argv).options(desc).positional(pod).run(),
      vm
      );
  bpo::notify( vm );
}

ALUGraph parseGraph( bpo::variables_map& vm )
{
  if ( vm.count("input-file") ) {
    string filename = vm["input-file"].as<string>();
    ifstream file( filename );
    return ALUGraph( file );
  } else {
    return ALUGraph( cin );
  }
}

int main( int argc, char **argv )
{
  bpo::options_description desc( "Allowed options" );
  bpo::variables_map vm;
  parse_program_options( argc, argv, desc, vm );

  // if help is requested, just print help and exit
  if ( vm.count("help") ) {
    cout << desc << endl;
    std::exit(EXIT_SUCCESS);
  }

  ALUGraph ug = parseGraph( vm );

  cout << "The graph is this: " << endl;
  cout << ug.toString();

  VertexID v_id;
  while (true) {
    cout << "Enter the vertex to search with, or a non-number to quit: ";
    cin >> v_id;
    if ( !cin )
      break;

    DepthFirstSearch<ALUGraph> dfs( ug, v_id, true, cout );

    cout << "There are " << dfs.count() << " vertices connected to " << v_id << endl;
  }

  return 0;
}
