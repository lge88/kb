#include <memory>
#include <queue>
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Edge { string from, to; };

vector<string> tsort(const vector<Edge>& edges) {
  unordered_map<string, vector<string> > adj;
  unordered_map<string, int> inEdges;
  for (auto edge : edges) {
    inEdges[edge.from] += 0;
    inEdges[edge.to] += 1;
    adj[edge.from].push_back(edge.to);
  }

  int remains = inEdges.size();
  queue<string> q;
  for (auto p : inEdges) {
    if (p.second == 0) {
      q.push(p.first);
      remains -= 1;
    }
  }

  vector<string> res;
  while (!q.empty()) {
    string u = move(q.front());
    q.pop();

    res.push_back(u);
    for (auto v : adj[u]) {
      inEdges[v] -= 1;
      if (inEdges[v] == 0) {
        q.push(v);
        remains -= 1;
      }
    }
  }

  return remains == 0 ? res : vector<string>();
}

int main(int argc, char* argv[]) {
  string line;
  vector<Edge> edges;
  while (getline(cin, line)) {
    istringstream iss(line);
    string u, v;
    iss >> u >> v;
    edges.push_back({ u, v });
  }

  vector<string> res = tsort(edges);
  for (auto u : res) cout << u << "\n";

  return 0;
}
