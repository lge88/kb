#ifndef DFS_GRAPH_TYPES_HH
#define DFS_GRAPH_TYPES_HH

#include "Graph.hh"
#include "GraphTextIO.hh"
#include "GraphBuilder.hh"

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

static const char colorToString[3][6] = { "WHITE", "GRAY", "BLACK" };
std::ostream& operator<<(std::ostream& to, const DfsVertexState& s) {
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
static const char edgeTypeToString[5][8] = { "UNKNOWN", "TREE", "BACK", "FORWARD", "CROSS" };
std::ostream& operator<<(std::ostream& to, const DfsEdgeState& s) {
  to << "{";
  to << " type=" << edgeTypeToString[s.type_];
  to << " }";
  return to;
}

typedef std::string DfsVertexIdType;
typedef Graph<DfsGraphState, DfsVertexState, DfsEdgeState, DfsVertexIdType> DfsGraph;
typedef GraphTextIO<DfsGraph> DfsGraphTextIO;
typedef GraphBuilder<DfsGraph> DfsGraphBuilder;

#endif // DFS_GRAPH_TYPES_HH
