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

template <typename StateType>
struct Vertex {
  const std::string id_;
  StateType state_;
  Vertex(const std::string& id) :
      id_(id)
  {}
};

template <typename VertexStateType>
class Graph {
 public:
  typedef Vertex<VertexStateType> V;

  Graph() {}

  bool addVertex(const std::string& id) {
    if (vertices_.find(id) != vertices_.end()) return false;
    vertices_.insert(std::make_pair(id, V(id)));
    return true;
  }

  bool hasVertex(const std::string& id) const {
    return vertices_.find(id) != vertices_.end();
  }

  const V& getVertex(const std::string& id) const {
    return vertices_.find(id)->second;
  }

  V& getMutableVertex(const std::string& id) {
    return vertices_.find(id)->second;
  }

  bool addEdge(const std::string& u, const std::string& v) {
    if (!hasVertex(u) || !hasVertex(v)) return false;

    adj_[u].insert(v);
    return true;
  }

  bool hasEdge(const std::string& u, const std::string& v) const {
    if (!hasVertex(u)) return false;
    const std::set<std::string>& neighbors = adj_.find(u)->second;
    return neighbors.find(v) != neighbors.end();
  }

  // Ideally should return a iterator
  std::vector<std::string> vertices() const {
    std::vector<std::string> out;
    for (typename std::map<std::string, V>::const_iterator it = vertices_.begin();
         it != vertices_.end();
         ++it) {
      out.push_back(it->first);
    }
    return out;
  }

  const std::set<std::string>& adj(const std::string& u) const {
    return adj_.find(u)->second;
  }

 private:
  std::map<std::string, V> vertices_;
  std::map<std::string, std::set<std::string> > adj_;
};

struct DfsState {
  enum Color {
    WHITE = 0,
    GRAY,
    BLACK
  };
  Color color_;
  std::string prev_;
  int discoveredTime_;
  int finishedTime_;
  DfsState() :
      color_(WHITE),
      prev_(""),
      discoveredTime_(-1),
      finishedTime_(-1)
  {}
};

typedef Graph<DfsState> MyGraph;

void printVertices(const MyGraph& g, std::ostream& out) {
  std::vector<std::string> colorToString(3);
  colorToString[0] = "WHITE";
  colorToString[1] = "GRAY";
  colorToString[2] = "BLACK";

  out << "Vertice:\n";

  const std::vector<std::string> vertices = g.vertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    const MyGraph::V& v = g.getVertex(vertices[i]);
    out << v.id_;
    out << ": color=" << colorToString[v.state_.color_];
    out << " prev=" << (v.state_.prev_ == "" ? "NULL" : v.state_.prev_);
    out << " d=" << v.state_.discoveredTime_;
    out << " f=" << v.state_.finishedTime_;
    out << "\n";
  }
}

void printEdges(const MyGraph& g, std::ostream& out) {
  out << "Edges:\n";

  const std::vector<std::string> vertices = g.vertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    const std::string& u = vertices[i];
    const std::set<std::string>& neighbors = g.adj(u);
    for (std::set<std::string>::const_iterator it = neighbors.begin();
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

void dfsVisit(MyGraph& g, int& time, const std::string& s) {
  MyGraph::V& sObj = g.getMutableVertex(s);

  time += 1;
  sObj.state_.color_ = DfsState::GRAY;
  sObj.state_.discoveredTime_ = time;

  std::vector<std::string> stack;
  stack.push_back(s);

  while (!stack.empty()) {
    const std::string u = stack.back();
    MyGraph::V& uObj = g.getMutableVertex(u);
    bool done = true;
    std::cout << "time: " << time << ", u: " << u << "\n";

    const std::set<std::string>& neighbors = g.adj(u);
    for (std::set<std::string>::const_iterator it = neighbors.begin();
         it != neighbors.end();
         ++it) {
      const std::string v = *it;
      MyGraph::V& vObj = g.getMutableVertex(v);
      if (vObj.state_.color_ == DfsState::WHITE) {
        time += 1;
        vObj.state_.color_ = DfsState::GRAY;
        vObj.state_.discoveredTime_ = time;
        vObj.state_.prev_ = u;
        stack.push_back(v);
        done = false;
        std::cout << "Edge Classification: " << u << " -> " << v << " : Tree\n";
        break;
      } else if (vObj.state_.color_ == DfsState::GRAY) {
        std::cout << "Edge Classification: " << u << " -> " << v << " : Back\n";
      } else {
        if (vObj.state_.prev_ == u) continue; // just poped
        if (uObj.state_.discoveredTime_ < vObj.state_.discoveredTime_) {
          std::cout << "Edge Classification: " << u << " -> " << v << " : Forward\n";
        } else {
          std::cout << "Edge Classification: " << u << " -> " << v << " : Cross\n";
        }
      }
    }

    if (done) {
      time += 1;
      uObj.state_.color_ = DfsState::BLACK;
      uObj.state_.finishedTime_ = time;
      stack.pop_back();
    }
  }
}

void dfs(MyGraph& g) {
  const std::vector<std::string> vertices = g.vertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    const std::string& u = vertices[i];
    MyGraph::V& uObj = g.getMutableVertex(u);
    uObj.state_.color_ = DfsState::WHITE;
    uObj.state_.prev_ = "";
  }

  int time = 0;
  for (size_t i = 0; i < vertices.size(); ++i) {
    const std::string& s = vertices[i];
    MyGraph::V& sObj = g.getMutableVertex(s);
    if (sObj.state_.color_ == DfsState::WHITE) {
      dfsVisit(g, time, s);
    }
  }
}

int main(int argc, char* argv[]) {
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

  return 0;
}
