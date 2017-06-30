/** \file UndirectedGraphDriver.cpp
 * Driver for UndirectedGraph
 *
 * \author Brian Heim
 * \date   2017-06-30
 */

#include "UndirectedGraph.hpp"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main()
{
  cout << "Driver for undirected graph" << endl;
  cout << "Enter the graph:" << endl;

  UndirectedGraph ug = UndirectedGraph( cin );

  cout << ug.toString();
  return 0;
}
