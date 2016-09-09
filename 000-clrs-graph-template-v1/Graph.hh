#ifndef GRAPH_HH
#define GRAPH_HH

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include <functional>

typedef std::string DefaultGraphState;
typedef std::string DefaultVertexState;
typedef std::string DefaultEdgeState;
typedef std::string DefaultVertexIdType;

template <typename GraphStateType = DefaultGraphState,
          typename VertexStateType = DefaultVertexState,
          typename EdgeStateType = DefaultEdgeState,
          typename VertexIdType = DefaultVertexIdType,
          bool directed = true>
class Graph {
 public:
  typedef typename std::vector<VertexIdType>::const_iterator VertexIterator;
  typedef GraphStateType GraphState;
  typedef VertexStateType VertexState;
  typedef EdgeStateType EdgeState;
  typedef VertexIdType VertexId;
  static const bool isDirected = directed;

  Graph() :
      numEdges_(0U)
  {}

  // Return false if u is already in graph
  bool addVertex(const VertexIdType& u) {
    if (hasVertex(u)) return false;

    vertices_.push_back(u);
    adj_.insert(std::make_pair(u, std::vector<VertexIdType>(0)));
    vertexStateMap_.insert(std::make_pair(u, VertexStateType()));
    return true;
  }

  // Return true if vertex u is in the graph.
  bool hasVertex(const VertexIdType& u) const {
    return adj_.find(u) != adj_.end();
  }

  // Return |V|
  size_t numVertices() const {
    return vertices_.size();
  }

  // Caller is responsible to make sure vertex u is in the graph.
  const VertexStateType& getVertexState(const VertexIdType& u) const {
    return vertexStateMap_.find(u)->second;
  }

  // Caller is responsible to make sure vertex u is in the graph.
  VertexStateType& getMutableVertexState(const VertexIdType& u) {
    return vertexStateMap_.find(u)->second;
  }

  // Caller is responsible to make sure edge (u, v) is in the graph.
  const EdgeStateType& getEdgeState(const VertexIdType& u, const VertexIdType& v) const {
    return edgeStateMap_.find(u)->second.find(v)->second;
  }

  // Caller is responsible to make sure edge (u, v) is in the graph.
  EdgeStateType& getMutableEdgeState(const VertexIdType& u, const VertexIdType& v) {
    return edgeStateMap_.find(u)->second.find(v)->second;
  }

  // Return a const graph state reference.
  const GraphStateType& getState() const {
    return state_;
  }

  // Return a mutable graph state reference.
  GraphStateType& getMutableState() {
    return state_;
  }

  // Return true if edge (u, v) is in the graph.
  bool hasEdge(const VertexIdType& u, const VertexIdType& v) const {
    return edgeStateMap_.find(u) != edgeStateMap_.end()
        && edgeStateMap_.find(u)->second.find(v) != edgeStateMap_.find(u)->second.end();
  }

  // Return false if u or v is not a vertex in the graph or (u, v)
  // already in the graph.
  bool addEdge(const VertexIdType& u, const VertexIdType& v) {
    if (!hasVertex(u) || !hasVertex(v) || hasEdge(u, v)) return false;
    adj_[u].push_back(v);
    edgeStateMap_[u][v] = EdgeStateType();
    ++numEdges_;
    return true;
  }

  // Return |E|
  size_t numEdges() const {
    return numEdges_;
  }

  // Return a iterator of all vertices.
  VertexIterator vertexBegin() const {
    return vertices_.begin();
  }

  // Return the end of all vertices iterator.
  VertexIterator vertexEnd() const {
    return vertices_.end();
  }

  // Caller is responsible to make sure u is in the graph.
  VertexIterator adjBegin(const std::string& u) const {
    return adj_.find(u)->second.begin();
  }

  // Return the end of adjacent vertices iterator.
  VertexIterator adjEnd(const std::string& u) const {
    return adj_.find(u)->second.end();
  }

 private:
  std::vector<VertexIdType> vertices_;
  std::unordered_map<VertexIdType, std::vector<VertexIdType> > adj_;
  size_t numEdges_;

  // States
  GraphStateType state_;

  std::unordered_map<VertexIdType, VertexStateType> vertexStateMap_;

  // 2D hash map of edge states
  std::unordered_map<
    VertexIdType,
    std::unordered_map<VertexIdType, EdgeStateType> > edgeStateMap_;
};

#endif // GRAPH_HH
