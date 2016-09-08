#include <iostream>
#include <string>
#include <vector>

#include "000-clrs-graph-template-v1/Graph.hh"
#include "000-clrs-graph-template-v1/GraphTextIO.hh"

struct DfsGraphState {
  int time_;
  DfsGraphState() :
      time_(0)
  {}
};

std::ostream& operator<<(std::ostream& to, const DfsGraphState& s) {
  to << "{ time=" << s.time_ << " }";
  return to;
}

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

std::ostream& operator<<(std::ostream& to, const DfsVertexState& s) {
  std::vector<std::string> colorToString(3);
  colorToString[0] = "WHITE";
  colorToString[1] = "GRAY";
  colorToString[2] = "BLACK";
  to << "{";
  to << " color=" << colorToString[s.color_];
  to << " prev=" << (s.prev_.empty() ? "NULL" : s.prev_);
  to << " discoveredTime=" << s.discoveredTime_;
  to << " finishedTime=" << s.finishedTime_;
  to << " }";
  return to;
}

struct DfsEdgeState {
  enum EdgeType {
    UNKNOWN = 0,
    TREE,
    BACK,
    FORWARD,
    CROSS
  };
  EdgeType type_;
  DfsEdgeState() :
      type_(UNKNOWN)
  {}
};

std::ostream& operator<<(std::ostream& to, const DfsEdgeState& s) {
  std::vector<std::string> edgeTypeToString(5);
  edgeTypeToString[0] = "UNKNOWN";
  edgeTypeToString[1] = "TREE";
  edgeTypeToString[2] = "BACK";
  edgeTypeToString[3] = "FORWARD";
  edgeTypeToString[4] = "CROSS";
  to << "{";
  to << " type=" << edgeTypeToString[s.type_];
  to << " }";
  return to;
}

typedef std::string DfsVertexIdType;
typedef Graph<DfsGraphState, DfsVertexState, DfsEdgeState, DfsVertexIdType> MyGraph;
typedef GraphTextIO<DfsGraphState, DfsVertexState, DfsEdgeState, DfsVertexIdType> MyGraphTextIO;

void dfsVisit(MyGraph& g, const std::string& s) {
  int& time = g.getMutableState().time_;
  DfsVertexState& sState = g.getMutableVertexState(s);

  time += 1;
  sState.color_ = DfsVertexState::GRAY;
  sState.discoveredTime_ = time;

  std::vector<std::pair<std::string, std::vector<std::string>::const_iterator> > stack;
  stack.push_back(std::make_pair(s, g.adjBegin(s)));

  while (!stack.empty()) {
    const std::string u = stack.back().first;
    MyGraph::VertexIterator vIter = stack.back().second;
    DfsVertexState& uState = g.getMutableVertexState(u);
    MyGraph::VertexIterator end = g.adjEnd(u);

    if (vIter != end) {
      const std::string v = *vIter;
      DfsVertexState& vState = g.getMutableVertexState(v);
      DfsEdgeState& eState = g.getMutableEdgeState(u, v);

      if (vState.color_ == DfsVertexState::WHITE) {
        eState.type_ = DfsEdgeState::TREE;
        time += 1;
        vState.color_ = DfsVertexState::GRAY;
        vState.discoveredTime_ = time;
        vState.prev_ = u;
        stack.push_back(std::make_pair(v, g.adjBegin(v)));
      } else {
        if (vState.color_ == DfsVertexState::GRAY) {
          eState.type_ = DfsEdgeState::BACK;
        } else {
          if (uState.discoveredTime_ < vState.discoveredTime_) {
            eState.type_ = DfsEdgeState::FORWARD;
          } else {
            eState.type_ = DfsEdgeState::CROSS;
          }
        }
        ++stack.back().second;
      }
    } else {
      time += 1;
      uState.color_ = DfsVertexState::BLACK;
      uState.finishedTime_ = time;
      stack.pop_back();
      if (!stack.empty()) ++stack.back().second;
    }
  }
}

void dfs(MyGraph& g) {
  for (MyGraph::VertexIterator uIter = g.vertexBegin();
       uIter != g.vertexEnd();
       ++uIter) {
    const std::string& u = *uIter;
    DfsVertexState& uState = g.getMutableVertexState(u);
    uState.color_ = DfsVertexState::WHITE;
    uState.prev_ = "";
  }

  int& time = g.getMutableState().time_;

  time = 0;
  for (MyGraph::VertexIterator sIter = g.vertexBegin();
       sIter != g.vertexEnd();
       ++sIter) {
    const std::string& s = *sIter;
    const DfsVertexState& sState = g.getVertexState(s);
    if (sState.color_ == DfsVertexState::WHITE) {
      dfsVisit(g, s);
    }
  }
}

int main(int argc, char* argv[]) {
  if (true) {
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

    MyGraphTextIO io(g);

    std::cout << "BEFORE DFS\n";
    io.writeDebug(std::cout);
    std::cout << "\n";

    dfs(g);

    std::cout << "AFTER DFS\n";
    io.writeDebug(std::cout);
    std::cout << "\n";
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

    MyGraphTextIO io(g);

    std::cout << "BEFORE DFS\n";
    io.writeDebug(std::cout);
    std::cout << "\n";

    dfs(g);

    std::cout << "AFTER DFS\n";
    io.writeDebug(std::cout);
    std::cout << "\n";
  }
  return 0;
}
