#include <iostream>
#include <string>
#include <sstream>

#include "Graph.hh"
#include "GraphTextIO.hh"
#include "GraphBuilder.hh"

int main(int argc, char* argv[]) {
  {
    Graph<> g1 = GraphBuilder<>::clrs_22_5_a();
    GraphTextIO<> g1IO(g1);

    std::cout << "g1:\n" << g1IO << "\n";

    g1IO.debug_ = true;
    std::cout << "g1 debug:\n" << g1IO << "\n";

    g1IO.debug_ = false;
    std::stringstream buf;
    buf << g1IO;

    Graph<> g2;
    GraphTextIO<> g2IO(g2);
    buf >> g2IO;

    std::cout << "g2:\n" << g2IO << "\n";
  }
  return 0;
}
