#ifndef GRAPH_Builder_HH
#define GRAPH_Builder_HH

#include "Graph.hh"

template <typename GraphType = Graph<> >
class GraphBuilder {
 public:

  // clrs Figure 22.4, page 605
  static GraphType clrs_22_4() {
    GraphType g;
    g.addVertex("u");
    g.addVertex("v");
    g.addVertex("w");
    g.addVertex("x");
    g.addVertex("y");
    g.addVertex("z");

    g.addEdge("u", "v");
    g.addEdge("u", "x");
    g.addEdge("v", "y");
    g.addEdge("w", "y");
    g.addEdge("w", "z");
    g.addEdge("x", "v");
    g.addEdge("y", "x");
    g.addEdge("z", "z");

    return g;
  }

  // clrs Figure 22.4, page 605
  static GraphType clrs_22_5_a() {
    GraphType g;
    g.addVertex("s");
    g.addVertex("z");
    g.addVertex("y");
    g.addVertex("x");
    g.addVertex("w");
    g.addVertex("t");
    g.addVertex("v");
    g.addVertex("u");

    g.addEdge("s", "z");
    g.addEdge("s", "w");
    g.addEdge("z", "y");
    g.addEdge("z", "w");
    g.addEdge("y", "x");
    g.addEdge("x", "z");
    g.addEdge("w", "x");
    g.addEdge("t", "v");
    g.addEdge("t", "u");
    g.addEdge("v", "s");
    g.addEdge("v", "w");
    g.addEdge("u", "v");
    g.addEdge("u", "t");

    return g;
  }
};

#endif // GRAPH_Builder_HH
