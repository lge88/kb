#ifndef GRAPH_TEXT_IO_HH
#define GRAPH_TEXT_IO_HH

#include "Graph.hh"

template <typename GraphType = Graph<> >
class GraphTextIO {
 public:

  GraphTextIO(GraphType& g) :
      g_(g)
  {}

  void writeVertices(std::ostream& to, bool debug = false) const {
    if (debug == true) to << "Number of vertices: ";
    to << g_.numVertices() << "\n";
    if (debug == true) to << "Vertices:\n";
    for (typename GraphType::VertexIterator uIter = g_.vertexBegin();
         uIter != g_.vertexEnd();
         ++uIter) {
      const typename GraphType::VertexId& u = *uIter;
      to << u;
      if (debug == true) {
        to << ": " << g_.getVertexState(u);
      }
      to << "\n";
    }
  }

  void writeEdges(std::ostream& to, bool debug = false) const {
    if (debug == true) to << "Number of edges: ";
    to << g_.numEdges() << "\n";
    if (debug == true) to << "Edges:\n";
    for (typename GraphType::VertexIterator uIter = g_.vertexBegin();
         uIter != g_.vertexEnd();
         ++uIter) {
      const typename GraphType::VertexId& u = *uIter;
      for (typename GraphType::VertexIterator vIter = g_.adjBegin(u);
           vIter != g_.adjEnd(u);
           ++vIter) {
        const typename GraphType::VertexId& v = *vIter;
        to << u
           << (debug ? " -> " : "\t")
           << v;
        if (debug == true) {
          to << ": " << g_.getEdgeState(u, v);
        }
        to << "\n";
      }
    }
  }

  void write(std::ostream& to, bool debug = false) const {
    writeVertices(to, debug);
    writeEdges(to, debug);
  }

  void writeDebug(std::ostream& to) const {
    to << "Graph state: " << g_.getState() << "\n";
    writeVertices(to, true);
    writeEdges(to, true);
  }

  void readVertices(std::istream& from) {
    size_t numVertices = 0;
    from >> numVertices;

    size_t i = 0;
    typename GraphType::VertexId u;
    while (i < numVertices && (from >> u)) {
      g_.addVertex(u);
      ++i;
    }

    if (i != numVertices) {
      throw std::runtime_error("Unmatched vertex number.");
    }
  }

  void readEdges(std::istream& from) {
    size_t numEdges = 0;
    from >> numEdges;

    size_t i = 0;
    typename GraphType::VertexId u, v;
    while (i < numEdges && (from >> u) && (from >> v)) {
      g_.addEdge(u, v);
      ++i;
    }

    if (i != numEdges) {
      throw std::runtime_error("Unmatched edge number.");
    }
  }

  void read(std::istream& from) {
    readVertices(from);
    readEdges(from);
  }

 private:
  GraphType& g_;

};

#endif // GRAPH_TEXT_IO_HH
