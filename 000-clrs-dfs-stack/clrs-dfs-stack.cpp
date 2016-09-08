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

template <typename VertexStateType, typename GraphStateType = int,
          typename VertexIdType = std::string, typename EdgeStateType = int>
class Graph {
 public:
  Graph() {}

  // Return false if u is already in graph
  bool addVertex(const VertexIdType& u) {
    if (hasVertex(u)) return false;

    vertices_.push_back(u);
    adj_.insert(std::make_pair(u, std::vector<VertexIdType>(0)));
    vertexStateMap_.insert(std::make_pair(u, VertexStateType()));
    return true;
  }

  bool hasVertex(const VertexIdType& u) const {
    return adj_.find(u) != adj_.end();
  }

  // Caller is responsible to make sure u is in the graph.
  const VertexStateType& getVertexState(const VertexIdType& u) const {
    return vertexStateMap_.find(u)->second;
  }

  // Caller is responsible to make sure u is in the graph.
  VertexStateType& getMutableVertexState(const VertexIdType& u) {
    return vertexStateMap_.find(u)->second;
  }

  const GraphStateType& getState() const {
    return state_;
  }

  GraphStateType& getMutableState() {
    return state_;
  }

  // Return false if u or v is not a vertex in the graph.
  bool addEdge(const VertexIdType& u, const VertexIdType& v) {
    if (!hasVertex(u) || !hasVertex(v)) return false;
    adj_[u].push_back(v);
    return true;
  }

  // Return a const reference of vertices. TODO: Ideally should return
  // a iterator.
  const std::vector<VertexIdType>& vertices() const {
    return vertices_;
  }

  // Caller is responsible to make sure u is in the graph.
  const std::vector<VertexIdType>& adj(const std::string& u) const {
    return adj_.find(u)->second;
  }

 private:
  std::vector<VertexIdType> vertices_;
  std::unordered_map<VertexIdType, std::vector<VertexIdType> > adj_;

  // States
  GraphStateType state_;
  std::unordered_map<VertexIdType, VertexStateType> vertexStateMap_;

  // TODO: edge state map
  // typedef std::tuple<VertexIdType, VertexIdType> EdgeIdType;
  // std::unordered_map<EdgeIdType, EdgeStateType> edgeStateMap_;
};

struct DfsVertexState {
  enum Color {
    WHITE = 0,
    GRAY,
    BLACK
  };
  Color color_;
  std::string prev_;
  int discoveredTime_;
  int finishedTime_;
  DfsVertexState() :
      color_(WHITE),
      prev_(""),
      discoveredTime_(-1),
      finishedTime_(-1)
  {}
};

struct DfsGraphState {
  int time_;
  DfsGraphState() :
      time_(0)
  {}
};

typedef Graph<DfsVertexState, DfsGraphState> MyGraph;

void printVertices(const MyGraph& g, std::ostream& out) {
  std::vector<std::string> colorToString(3);
  colorToString[0] = "WHITE";
  colorToString[1] = "GRAY";
  colorToString[2] = "BLACK";

  out << "Vertice:\n";

  const std::vector<std::string>& vertices = g.vertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    const std::string& u = vertices[i];
    const DfsVertexState& uState = g.getVertexState(u);

    out << u;
    out << ": color=" << colorToString[uState.color_];
    out << " prev=" << (uState.prev_ == "" ? "NULL" : uState.prev_);
    out << " d=" << uState.discoveredTime_;
    out << " f=" << uState.finishedTime_;
    out << "\n";
  }
}

void printEdges(const MyGraph& g, std::ostream& out) {
  out << "Edges:\n";

  const std::vector<std::string>& vertices = g.vertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    const std::string& u = vertices[i];
    const std::vector<std::string>& neighbors = g.adj(u);
    for (std::vector<std::string>::const_iterator it = neighbors.begin();
         it != neighbors.end();
         ++it) {
      const std::string& v = *it;
      out << u << " -> " << v << "\n";
    }
  }
}

void printMyGraph(const MyGraph& g, std::ostream& out) {
  printVertices(g, out);
  out << "\n";
  printEdges(g, out);
}

void dfsVisit(MyGraph& g, const std::string& s) {
  int& time = g.getMutableState().time_;

  DfsVertexState& sState = g.getMutableVertexState(s);

  time += 1;
  sState.color_ = DfsVertexState::GRAY;
  sState.discoveredTime_ = time;

  std::vector<std::pair<std::string, std::vector<std::string>::const_iterator> > stack;
  stack.push_back(std::make_pair(s, g.adj(s).begin()));

  while (!stack.empty()) {
    const std::string u = stack.back().first;
    DfsVertexState& uState = g.getMutableVertexState(u);
    std::vector<std::string>::const_iterator& it = stack.back().second;
    const std::vector<std::string>& neighbors = g.adj(u);

    if (it != neighbors.end()) {
      const std::string v = *it;
      DfsVertexState& vState = g.getMutableVertexState(v);

      if (vState.color_ == DfsVertexState::WHITE) {
        std::cout << "Edge Classification: " << u << " -> " << v << " : Tree\n";
        time += 1;
        vState.color_ = DfsVertexState::GRAY;
        vState.discoveredTime_ = time;
        vState.prev_ = u;
        stack.push_back(std::make_pair(v, g.adj(v).begin()));
      } else if (vState.color_ == DfsVertexState::GRAY) {
        std::cout << "Edge Classification: " << u << " -> " << v << " : Back\n";
        ++it;
      } else {
        if (uState.discoveredTime_ < vState.discoveredTime_) {
          std::cout << "Edge Classification: " << u << " -> " << v << " : Forward\n";
        } else {
          std::cout << "Edge Classification: " << u << " -> " << v << " : Cross\n";
        }
        ++it;
      }
    } else {
      time += 1;
      uState.color_ = DfsVertexState::BLACK;
      uState.finishedTime_ = time;
      stack.pop_back();
      // advance parent iterator
      if (!stack.empty()) ++stack.back().second;
    }
  }
}

void dfs(MyGraph& g) {
  const std::vector<std::string>& vertices = g.vertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    const std::string& u = vertices[i];
    DfsVertexState& uState = g.getMutableVertexState(u);
    uState.color_ = DfsVertexState::WHITE;
    uState.prev_ = "";
  }

  int& time = g.getMutableState().time_;

  time = 0;
  for (size_t i = 0; i < vertices.size(); ++i) {
    const std::string& s = vertices[i];
    const DfsVertexState& sState = g.getVertexState(s);
    if (sState.color_ == DfsVertexState::WHITE) {
      dfsVisit(g, s);
    }
  }
}

int main(int argc, char* argv[]) {
  if (false) {
    // clrs Figure 22.4, page 605
    MyGraph g;
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

    std::cout << "BEFORE DFS\n";
    printMyGraph(g, std::cout);
    std::cout << "\n";

    dfs(g);
    std::cout << "\n";

    std::cout << "AFTER DFS\n";
    printMyGraph(g, std::cout);
  }

  if (true) {
    // clrs Figure 22.5(a), page 607
    MyGraph g;
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

    std::cout << "BEFORE DFS\n";
    printMyGraph(g, std::cout);
    std::cout << "\n";

    dfs(g);
    std::cout << "\n";

    std::cout << "AFTER DFS\n";
    printMyGraph(g, std::cout);
  }
  return 0;
}
