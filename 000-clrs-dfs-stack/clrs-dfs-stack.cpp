#include <iostream>
#include <string>
#include <vector>

#include "000-clrs-graph-template-v1/DfsGraphTypes.hh"

typedef DfsGraph::GraphState GraphState;
typedef DfsGraph::VertexState VertexState;
typedef DfsGraph::EdgeState EdgeState;
typedef DfsGraph::VertexIterator VertexIterator;
typedef DfsGraph::VertexId VertexId;
typedef std::vector<std::pair<VertexId, VertexIterator> > Stack;

void dfsVisit(DfsGraph& g, const VertexId& s) {
  int& time = g.getMutableState().time_;
  VertexState& sState = g.getMutableVertexState(s);

  time += 1;
  sState.color_ = DfsVertexState::GRAY;
  sState.discoveredTime_ = time;

  Stack stack;
  stack.push_back(std::make_pair(s, g.adjBegin(s)));

  while (!stack.empty()) {
    const VertexId u = stack.back().first;
    VertexIterator vIter = stack.back().second;
    VertexState& uState = g.getMutableVertexState(u);
    VertexIterator end = g.adjEnd(u);

    if (vIter != end) {
      const VertexId v = *vIter;
      VertexState& vState = g.getMutableVertexState(v);
      EdgeState& eState = g.getMutableEdgeState(u, v);

      if (vState.color_ == VertexState::WHITE) {
        eState.type_ = EdgeState::TREE;
        time += 1;
        vState.color_ = VertexState::GRAY;
        vState.discoveredTime_ = time;
        vState.prev_ = u;
        stack.push_back(std::make_pair(v, g.adjBegin(v)));
      } else {
        if (vState.color_ == VertexState::GRAY) {
          eState.type_ = EdgeState::BACK;
        } else {
          if (uState.discoveredTime_ < vState.discoveredTime_) {
            eState.type_ = EdgeState::FORWARD;
          } else {
            eState.type_ = EdgeState::CROSS;
          }
        }
        ++stack.back().second;
      }
    } else {
      time += 1;
      uState.color_ = VertexState::BLACK;
      uState.finishedTime_ = time;
      stack.pop_back();
      if (!stack.empty()) ++stack.back().second;
    }
  }
}

void dfs(DfsGraph& g) {
  for (VertexIterator uIter = g.vertexBegin();
       uIter != g.vertexEnd();
       ++uIter) {
    const VertexId& u = *uIter;
    VertexState& uState = g.getMutableVertexState(u);
    uState.color_ = VertexState::WHITE;
    uState.prev_ = "";
  }

  int& time = g.getMutableState().time_;
  time = 0;
  for (VertexIterator sIter = g.vertexBegin();
       sIter != g.vertexEnd();
       ++sIter) {
    const VertexId& s = *sIter;
    const VertexState& sState = g.getVertexState(s);
    if (sState.color_ == VertexState::WHITE) {
      dfsVisit(g, s);
    }
  }
}

int main(int argc, char* argv[]) {
  if (true) {
    // clrs Figure 22.4, page 605
    DfsGraph g = DfsGraphBuilder::clrs_22_4();
    DfsGraphTextIO io(g);

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
    DfsGraph g = DfsGraphBuilder::clrs_22_5_a();
    DfsGraphTextIO io(g);

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
