/** \file UGraphDriver.cpp
 * Driver for UndirectedGraph
 *
 * \author Brian Heim
 * \date   2017-06-30
 */

#include "AbstractUGraph.hpp"
#include "AMUGraph.hpp"
#include "ALUGraph.hpp"

#include <iostream>
#include <string>

using std::string;
using std::cin;
using std::cout;
using std::endl;

AbstractUGraph * create_graph( string opt )
{
  if ( opt == "-m" )
    return new AMUGraph( cin );
  else if ( opt == "-l" )
    return new ALUGraph( cin );
  else
    throw std::runtime_error( "Unknown argument: " + opt );
}

int main(int argc, char **argv)
{
  string opt;

  // default is to use an adjacency list
  if ( argc == 1 )
    opt = "-l";
  else
    opt = *++argv;

  cout << "Undirected graph creation driver. Enter your graph: " << endl;
  AbstractUGraph * ug = create_graph( opt );

  cout << ug->toString();
  return 0;
}
