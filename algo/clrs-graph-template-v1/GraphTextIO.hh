#ifndef GRAPH_TEXT_IO_HH
#define GRAPH_TEXT_IO_HH

#include "Graph.hh"

template <typename GraphType = Graph<> >
class GraphTextIO {
 private:
  static const bool isDirected_ = GraphType::isDirected_;

 public:
  bool debug_;
  bool shouldWriteEdge_;

 private:
  const char* sep_ = (isDirected_ ? " -> " : " - ");
  GraphType& g_;

 public:
  GraphTextIO(GraphType& g) :
      debug_(false),
      shouldWriteEdge_(true),
      g_(g)
  {}

  void writeVertices(std::ostream& to) const {
    if (debug_ == true) to << "Number of vertices: ";
    to << g_.numVertices() << "\n";
    if (debug_ == true) to << "Vertices:\n";
    for (typename GraphType::VertexIterator uIter = g_.vertexBegin();
         uIter != g_.vertexEnd();
         ++uIter) {
      const typename GraphType::VertexId& u = *uIter;
      to << u;
      if (debug_ == true) {
        to << ": " << g_.getVertexState(u);
      }
      to << "\n";
    }
  }

  void writeEdges(std::ostream& to) const {
    if (debug_ == true) to << "Number of edges: ";
    to << g_.numEdges() << "\n";
    if (debug_ == true) to << "Edges:\n";
    for (typename GraphType::VertexIterator uIter = g_.vertexBegin();
         uIter != g_.vertexEnd();
         ++uIter) {
      const typename GraphType::VertexId& u = *uIter;
      for (typename GraphType::VertexIterator vIter = g_.adjBegin(u);
           vIter != g_.adjEnd(u);
           ++vIter) {
        const typename GraphType::VertexId& v = *vIter;
        to << u
           << (debug_ ? sep_ : "\t")
           << v;
        if (debug_ == true) {
          to << ": " << g_.getEdgeState(u, v);
        }
        to << "\n";
      }
    }
  }

  void write(std::ostream& to) const {
    if (debug_) {
      to << "Graph isDirected: " << g_.isDirected() << "\n";
      to << "Graph state: " << g_.getState() << "\n";
    }
    writeVertices(to);
    if (shouldWriteEdge_) writeEdges(to);
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

};

template <typename GraphType = Graph<> >
std::ostream& operator<<(std::ostream& to, const GraphTextIO<GraphType>& io) {
  io.write(to);
  return to;
}

template <typename GraphType = Graph<> >
std::istream& operator>>(std::istream& from, GraphTextIO<GraphType>& io) {
  io.read(from);
  return from;
}

#endif // GRAPH_TEXT_IO_HH
