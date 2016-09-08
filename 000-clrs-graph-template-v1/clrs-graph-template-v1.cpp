#include <iostream>
#include <string>
#include <sstream>

#include "Graph.hh"
#include "GraphTextIO.hh"

int main(int argc, char* argv[]) {
  {
    // clrs Figure 22.5(a), page 607
    Graph<> g1;
    g1.addVertex("s");
    g1.addVertex("z");
    g1.addVertex("y");
    g1.addVertex("x");
    g1.addVertex("w");
    g1.addVertex("t");
    g1.addVertex("v");
    g1.addVertex("u");

    g1.addEdge("s", "z");
    g1.addEdge("s", "w");
    g1.addEdge("z", "y");
    g1.addEdge("z", "w");
    g1.addEdge("y", "x");
    g1.addEdge("x", "z");
    g1.addEdge("w", "x");
    g1.addEdge("t", "v");
    g1.addEdge("t", "u");
    g1.addEdge("v", "s");
    g1.addEdge("v", "w");
    g1.addEdge("u", "v");
    g1.addEdge("u", "t");

    GraphTextIO<> g1IO(g1);

    std::cout << "g1:\n";
    g1IO.write(std::cout);
    std::cout << "\n";

    std::cout << "g1 debug:\n";
    g1IO.writeDebug(std::cout);
    std::cout << "\n";

    std::stringstream buf;
    g1IO.write(buf);

    Graph<> g2;
    GraphTextIO<> g2IO(g2);
    g2IO.read(buf);

    std::cout << "g2:\n";
    g2IO.write(std::cout);
    std::cout << "\n";
  }
  return 0;
}
