#include <iostream>
#include <string>
#include <vector>
#include "clrs-graph-template-v1/DfsGraphTypes.hh"

typedef DfsGraph::GraphState GraphState;
typedef DfsGraph::VertexState VertexState;
typedef DfsGraph::EdgeState EdgeState;
typedef DfsGraph::VertexIterator VertexIterator;
typedef DfsGraph::VertexId VertexId;

void dfsVisit(DfsGraph& g, const VertexId& u) {
  int& time = g.getMutableState().time_;
  VertexState& uState = g.getMutableVertexState(u);

  time += 1;
  uState.discoveredTime_ = time;
  uState.color_ = VertexState::GRAY;

  for (VertexIterator it = g.adjBegin(u);
       it != g.adjEnd(u);
       ++it) {
    const std::string& v = *it;
    VertexState& vState = g.getMutableVertexState(v);
    EdgeState& eState = g.getMutableEdgeState(u, v);
    if (vState.color_ == VertexState::WHITE) {
      eState.type_ = EdgeState::TREE;
      vState.prev_ = u;
      dfsVisit(g, v);
    } else if (vState.color_ == VertexState::GRAY) {
      eState.type_ = EdgeState::BACK;
    } else {
      // vVertex is BLACK
      if (uState.discoveredTime_ < vState.discoveredTime_) {
        eState.type_ = EdgeState::FORWARD;
      } else {
        eState.type_ = EdgeState::CROSS;
      }
    }
  }

  uState.color_ = VertexState::BLACK;
  time += 1;
  uState.finishedTime_ = time;
}

void dfs(DfsGraph& g) {
  for (VertexIterator it = g.vertexBegin(); it != g.vertexEnd(); ++it) {
    const std::string& u = *it;
    DfsVertexState& uState = g.getMutableVertexState(u);
    uState.color_ = VertexState::WHITE;
    uState.prev_ = "";
  }

  int& time = g.getMutableState().time_;
  time = 0;
  for (VertexIterator it = g.vertexBegin(); it != g.vertexEnd(); ++it) {
    const std::string& u = *it;
    if (g.getVertexState(u).color_ == VertexState::WHITE)
      dfsVisit(g, u);
  }
}

int main(int argc, char* argv[]) {
  if (true) {
    // clrs Figure 22.4, page 605
    DfsGraph g = DfsGraphBuilder::clrs_22_4();
    DfsGraphTextIO io(g);
    io.debug_ = true;

    std::cout << "BEFORE DFS:\n" << io << "\n";

    dfs(g);

    std::cout << "AFTER DFS:\n" << io << "\n";
  }

  if (true) {
    // clrs Figure 22.5(a), page 607
    DfsGraph g = DfsGraphBuilder::clrs_22_5_a();
    DfsGraphTextIO io(g);
    io.debug_ = true;

    std::cout << "BEFORE DFS:\n" << io << "\n";

    dfs(g);

    std::cout << "AFTER DFS:\n" << io << "\n";
  }

  return 0;
}
