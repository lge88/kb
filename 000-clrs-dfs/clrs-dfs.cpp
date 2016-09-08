#include <iostream>
#include <string>
#include <vector>

#include "000-clrs-graph-template-v1/Graph.hh"
#include "000-clrs-graph-template-v1/GraphTextIO.hh"
#include "000-clrs-graph-template-v1/GraphBuilder.hh"

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
typedef GraphBuilder<DfsGraphState, DfsVertexState, DfsEdgeState, DfsVertexIdType> MyGraphBuilder;

void dfsVisit(MyGraph& g, const std::string& u) {
  int& time = g.getMutableState().time_;
  DfsVertexState& uState = g.getMutableVertexState(u);

  time += 1;
  uState.discoveredTime_ = time;
  uState.color_ = DfsVertexState::GRAY;

  for (MyGraph::VertexIterator it = g.adjBegin(u);
       it != g.adjEnd(u);
       ++it) {
    const std::string& v = *it;
    DfsVertexState& vState = g.getMutableVertexState(v);
    DfsEdgeState& eState = g.getMutableEdgeState(u, v);
    if (vState.color_ == DfsVertexState::WHITE) {
      eState.type_ = DfsEdgeState::TREE;
      vState.prev_ = u;
      dfsVisit(g, v);
    } else if (vState.color_ == DfsVertexState::GRAY) {
      eState.type_ = DfsEdgeState::BACK;
    } else {
      // vVertex is BLACK
      if (uState.discoveredTime_ < vState.discoveredTime_) {
        eState.type_ = DfsEdgeState::FORWARD;
      } else {
        eState.type_ = DfsEdgeState::CROSS;
      }
    }
  }

  uState.color_ = DfsVertexState::BLACK;
  time += 1;
  uState.finishedTime_ = time;
}

void dfs(MyGraph& g) {
  for (MyGraph::VertexIterator it = g.vertexBegin(); it != g.vertexEnd(); ++it) {
    const std::string& u = *it;
    DfsVertexState& uState = g.getMutableVertexState(u);
    uState.color_ = DfsVertexState::WHITE;
    uState.prev_ = "";
  }

  int& time = g.getMutableState().time_;
  time = 0;
  for (MyGraph::VertexIterator it = g.vertexBegin(); it != g.vertexEnd(); ++it) {
    const std::string& u = *it;
    if (g.getVertexState(u).color_ == DfsVertexState::WHITE)
      dfsVisit(g, u);
  }
}

int main(int argc, char* argv[]) {
  if (true) {
    // clrs Figure 22.4, page 605
    MyGraph g = MyGraphBuilder::clrs_22_4();
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
    MyGraph g = MyGraphBuilder::clrs_22_5_a();
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
