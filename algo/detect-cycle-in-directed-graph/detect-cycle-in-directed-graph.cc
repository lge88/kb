#include <iostream>
#include <vector>

using namespace std;

struct Edge { int from, to; };
enum class Color { WHITE, GRAY, BLACK };

bool dfs(int u, const vector<vector<int>>& adj, vector<Color>& colors);

bool hasCycle(int V, const vector<Edge>& edges) {
  vector<vector<int>> adj(V);
  for (auto edge: edges) {
    adj[edge.from].push_back(edge.to);
  }

  vector<Color> colors(V, Color::WHITE);
  for (int u = 0; u < V; ++u) {
    if (colors[u] == Color::WHITE && dfs(u, adj, colors)) {
      return true;
    }
  }
  return false;
}

bool dfs(int u, const vector<vector<int>>& adj, vector<Color>& colors) {
  colors[u] = Color::GRAY;
  for (int v : adj[u]) {
    if (colors[v] == Color::WHITE && dfs(v, adj, colors)) {
      return true;
    }
    if (colors[v] == Color::GRAY) {
      return true;
    }
  }
  colors[u] = Color::BLACK;
  return false;
}

int main(int argc, char* argv[]) {
  int V, E;
  cin >> V >> E;

  vector<Edge> edges;
  for (int i = 0; i < E; ++i) {
    int u, v;
    cin >> u >> v;
    edges.push_back({ u, v });
  }

  cout << hasCycle(V, edges) << "\n";

  return 0;
}
