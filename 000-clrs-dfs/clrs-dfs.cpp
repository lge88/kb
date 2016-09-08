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

struct Vertex {
  std::string id_;
  enum Color {
    WHITE = 0,
    GRAY,
    BLACK
  };
  Color color_;
  std::string prev_;
  int discoveredTime_;
  int finishedTime_;

  std::string val_;
  Vertex() :
      id_(""),
      color_(WHITE),
      prev_(""),
      discoveredTime_(0),
      finishedTime_(0),
      val_("")
  {}
};

class Graph {
  std::map<std::string, Vertex> vertices_;
  std::map<std::string, std::set<std::string> > adj_;

 public:
  Graph() {}
  bool addVertex(const std::string& id, const std::string& val) {
    if (vertices_.find(id) != vertices_.end()) return false;

    Vertex v;
    v.id_ = id;
    v.val_ = val;
    vertices_[v.id_] = v;
    return true;
  }

  bool addVertex(const std::string& id) {
    return addVertex(id, id);
  }

  bool hasVertex(const std::string& id) const {
    return vertices_.find(id) != vertices_.end();
  }

  const Vertex& getVertex(const std::string& id) const {
    return vertices_.find(id)->second;
  }

  Vertex& getMutableVertex(const std::string& id) {
    return vertices_.find(id)->second;
  }

  bool addEdge(const std::string& u, const std::string& v) {
    if (!hasVertex(u) || !hasVertex(v)) return false;

    adj_[u].insert(v);
    return true;
  }

  bool hasEdge(const std::string& from, const std::string& to) const {
    if (!hasVertex(from)) return false;
    const std::set<std::string>& neighbors = adj_.find(from)->second;
    return neighbors.find(to) != neighbors.end();
  }

  // Ideally should return a iterator
  std::vector<std::string> vertices() const {
    std::vector<std::string> out;
    for (std::map<std::string, Vertex>::const_iterator it = vertices_.begin();
         it != vertices_.end();
         ++it) {
      out.push_back(it->first);
    }
    return out;
  }

  const std::set<std::string>& adj(const std::string& u) const {
    return adj_.find(u)->second;
  }

  void printVertices(std::ostream& out) const {
    std::vector<std::string> colorToString(3);
    colorToString[0] = "WHITE";
    colorToString[1] = "GRAY";
    colorToString[2] = "BLACK";

    out << "Vertice:\n";
    for (std::map<std::string, Vertex>::const_iterator it = vertices_.begin();
         it != vertices_.end();
         ++it) {
      const Vertex& v = getVertex(it->first);
      out << v.id_;
      out << ": color=" << colorToString[v.color_];
      out << " prev=" << (v.prev_ == "" ? "NULL" : v.prev_);
      out << " d=" << v.discoveredTime_;
      out << " f=" << v.finishedTime_;
      out << " val=" << v.val_;
      out << "\n";
    }
  }

  void printEdges(std::ostream& out) const {
    out << "Edges:\n";
    for (std::map<std::string, std::set<std::string> >::const_iterator it = adj_.begin();
         it != adj_.end();
         ++it) {
      const std::string& from = it->first;
      const std::set<std::string>& neighbors = adj(it->first);
      for (std::set<std::string>::const_iterator it2 = neighbors.begin();
           it2 != neighbors.end();
           ++it2) {
        const std::string& to = *it2;
        out << from << " -> " << to << "\n";
      }
    }
  }

  void print(std::ostream& out) const {
    printVertices(out);
    out << "\n";
    printEdges(out);
  }

};

void dfsVisit(Graph& g, int& time, const std::string& u) {
  std::cout << "time: " << time << ", at " << u << "\n";
  g.printVertices(std::cout);
  std::cout << "\n";

  Vertex& uVertex = g.getMutableVertex(u);

  time += 1;
  uVertex.discoveredTime_ = time;
  uVertex.color_ = Vertex::GRAY;

  const std::set<std::string> neighbors = g.adj(u);
  for (std::set<std::string>::const_iterator it = neighbors.begin();
       it != neighbors.end();
       ++it) {
    const std::string& v = *it;
    Vertex& vVertex = g.getMutableVertex(v);
    if (vVertex.color_ == Vertex::WHITE) {
      std::cout << "Edge Classification: " << u << " -> " << v << " : Tree\n";
      vVertex.prev_ = u;
      dfsVisit(g, time, v);
    } else if (vVertex.color_ == Vertex::GRAY) {
      std::cout << "Edge Classification: " << u << " -> " << v << " : Back\n";
    } else {
      // vVertex is BLACK
      if (uVertex.discoveredTime_ < vVertex.discoveredTime_) {
        std::cout << "Edge Classification: " << u << " -> " << v << " : Forward\n";
      } else {
        std::cout << "Edge Classification: " << u << " -> " << v << " : Cross\n";
      }
    }
  }

  uVertex.color_ = Vertex::BLACK;
  time += 1;
  uVertex.finishedTime_ = time;
}

void dfs(Graph& g) {
  const std::vector<std::string> vertices = g.vertices();
  for (size_t i = 0; i < vertices.size(); ++i) {
    const std::string& u = vertices[i];
    Vertex& uVertex = g.getMutableVertex(u);
    uVertex.color_ = Vertex::WHITE;
    uVertex.prev_ = "";
  }

  int time = 0;
  for (size_t i = 0; i < vertices.size(); ++i) {
    const std::string& u = vertices[i];
    if (g.getVertex(u).color_ == Vertex::WHITE)
      dfsVisit(g, time, u);
  }
}

int main(int argc, char* argv[]) {
  {
    Graph g;
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
    g.print(std::cout);
    std::cout << "\n";

    dfs(g);
    std::cout << "\n";

    std::cout << "AFTER DFS\n";
    g.print(std::cout);
  }

  {
    Graph g;
    g.addVertex("y");
    g.addVertex("z");
    g.addVertex("s");
    g.addVertex("t");
    g.addVertex("x");
    g.addVertex("w");
    g.addVertex("v");
    g.addVertex("u");

    g.addEdge("y", "x");
    g.addEdge("z", "y");
    g.addEdge("z", "w");
    g.addEdge("s", "z");
    g.addEdge("s", "w");
    g.addEdge("t", "v");
    g.addEdge("t", "u");
    g.addEdge("x", "z");
    g.addEdge("w", "x");
    g.addEdge("v", "s");
    g.addEdge("v", "w");
    g.addEdge("u", "t");
    g.addEdge("u", "v");

    std::cout << "BEFORE DFS\n";
    g.print(std::cout);
    std::cout << "\n";

    dfs(g);
    std::cout << "\n";

    std::cout << "AFTER DFS\n";
    g.print(std::cout);
  }

  return 0;
}
