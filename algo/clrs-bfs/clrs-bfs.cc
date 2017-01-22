#include <queue>

#include "clrs-graph-template-v1/Graph.hh"
#include "clrs-graph-template-v1/GraphTextIO.hh"
#include "clrs-graph-template-v1/GraphBuilder.hh"

typedef std::string BfsVertexIdType;
typedef std::string BfsGraphState;
typedef std::string BfsEdgeState;

struct BfsVertexState {
  enum Color {
    WHITE = 0,
    GRAY,
    BLACK
  };
  Color color_;
  int d_;
  BfsVertexIdType prev_;
  BfsVertexState() :
      color_(WHITE),
      d_(-1),
      prev_("")
  {}
};

static const char colorToString[3][6] = { "WHITE", "GRAY", "BLACK" };
std::ostream& operator<<(std::ostream& to, const BfsVertexState& s) {
  to << "{";
  to << " color=" << colorToString[s.color_];
  to << " d=" << s.d_;
  to << " prev=" << (s.prev_.empty() ? "NULL" : s.prev_);
  to << " }";
  return to;
}

template <typename G>
void bfs(G& g, const typename G::VertexId& s) {
  typedef std::queue<typename G::VertexId> Queue;
  typedef typename G::VertexState VertexState;

  VertexState& sState = g.getMutableVertexState(s);
  sState.color_ = VertexState::GRAY;
  sState.d_ = 0;
  sState.prev_ = "";

  Queue q;
  q.push(s);

  while (!q.empty()) {
    const typename G::VertexId u = q.front();
    VertexState& uState = g.getMutableVertexState(u);
    q.pop();

    for (typename G::VertexIterator vIter = g.adjBegin(u); vIter != g.adjEnd(u); ++vIter) {
      const typename G::VertexId v = *vIter;
      VertexState& vState = g.getMutableVertexState(v);
      if (vState.color_ == VertexState::WHITE) {
        vState.color_ = VertexState::GRAY;
        vState.d_ = uState.d_ + 1;
        vState.prev_ = u;
        q.push(v);
      }
    }

    uState.color_ = VertexState::BLACK;
  }

  return;
}

typedef UndirectedGraph<BfsGraphState, BfsVertexState, BfsEdgeState, BfsVertexIdType> G;
int main(int argc, char* argv[]) {
  {
    G g = GraphBuilder<G>::clrs_22_3();
    GraphTextIO<G> io(g);
    io.debug_ = true;
    io.shouldWriteEdge_ = false;

    std::cout << "BEFORE BFS:\n" << io << "\n";

    bfs(g, "s");

    std::cout << "AFTER BFS:\n" << io << "\n";
  }
  return 0;
}
