/** \file FindCycleDriver.cpp
 * Driver for findCycle
 *
 * \author Brian Heim
 * \date   2017-07-21
 */

#include "AbstractUGraph.hpp"
#include "AMUGraph.hpp"
#include "ALUGraph.hpp"
#include "GraphInfo.hpp"

#include <boost/program_options.hpp>

#include <iostream>
#include <fstream> // ifstream
#include <string> // string
#include <vector>
#include <array>
#include <numeric>
#include <experimental/optional>

using std::string;
using std::ifstream;
using std::cin;
using std::cout;
using std::endl;
using std::array;
using std::vector;

using VertexID = AbstractUGraph::VertexID;
namespace bpo = boost::program_options;

void parseProgramOptions( int argc, char **argv, bpo::options_description& desc, bpo::variables_map& vm )
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
  parseProgramOptions( argc, argv, desc, vm );

  // if help is requested, just print help and exit
  if ( vm.count("help") ) {
    cout << desc << endl;
    std::exit( EXIT_SUCCESS );
  }

  ALUGraph ug = parseGraph( vm );

  cout << "The graph is this: " << endl;
  cout << ug.toString();

  auto maybeCycle = GraphInfo::findCycle( ug );
  typedef std::vector<VertexID> Path;

  if ( maybeCycle ) {
    cout << "Got a cycle. Here it is: " << endl;
    for ( Path::const_iterator it = maybeCycle->cbegin(); it != maybeCycle->cend(); ++it )
      cout << "\t" << *it;
    cout << endl;
  } else {
    cout << "No cycle, sorry." << endl;
  }

  std::exit( EXIT_SUCCESS );
}

