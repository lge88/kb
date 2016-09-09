#include <iostream>
#include <string>
#include <sstream>

#include "Graph.hh"
#include "GraphTextIO.hh"
#include "GraphBuilder.hh"

int main(int argc, char* argv[]) {
  if (true) {
    // Test write, read, debug output.
    DirectedGraph<> g1 = GraphBuilder<DirectedGraph<> >::clrs_22_5_a();
    GraphTextIO<DirectedGraph<> > g1IO(g1);

    std::cout << "g1:\n" << g1IO << "\n";

    g1IO.debug_ = true;
    std::cout << "g1 debug:\n" << g1IO << "\n";

    g1IO.debug_ = false;
    std::stringstream buf;
    buf << g1IO;

    DirectedGraph<> g2;
    GraphTextIO<DirectedGraph<> > g2IO(g2);
    buf >> g2IO;

    std::cout << "g2:\n" << g2IO << "\n";
  }

  if (true) {
    // Test undirected graph
    UndirectedGraph<> g = GraphBuilder<UndirectedGraph<> >::clrs_22_3();
    GraphTextIO<UndirectedGraph<> > gIO(g);
    gIO.debug_ = true;
    std::cout << "g debug:\n" << gIO << "\n";
  }
  return 0;
}
