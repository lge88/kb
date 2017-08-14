#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Graph {
  int V;
  vector<vector<int> > adj;
};

void dfs(int u, const Graph& g, vector<int>& indegree, vector<int>& path, set<int>& sources);

void tsortPrintAll(const Graph& g) {
  vector<int> indegree(g.V, 0);
  for (auto edge : g.adj) {
    for (auto v : edge) {
      indegree[v] += 1;
    }
  }

  set<int> sources;
  for (int u = 0; u < g.V; ++u) {
    if (indegree[u] == 0) sources.insert(u);
  }

  vector<int> path;

  // Need this copy since in within each iteration, sources are mutated.
  vector<int> sourcesCopy(sources.begin(), sources.end());
  for (auto u : sourcesCopy) {
    path.push_back(u);
    sources.erase(u);

    dfs(u, g, indegree, path, sources);

    sources.insert(u);
    path.pop_back();
  }
}

void dfs(int u, const Graph& g, vector<int>& indegree, vector<int>& path, set<int>& sources) {
  if (path.size() == g.V) {
    cout << "[";
    for (auto u : path) cout << " " << u;
    cout << " ]\n";
    return;
  }

  for (auto v : g.adj[u]) {
    indegree[v] -= 1;
    if (indegree[v] == 0) sources.insert(v);
  }

  // Need this copy since in within each iteration, sources are mutated.
  vector<int> sourcesCopy(sources.begin(), sources.end());
  for (auto v : sourcesCopy) {
    path.push_back(v);
    sources.erase(v);

    dfs(v, g, indegree, path, sources);

    sources.insert(v);
    path.pop_back();
  }

  for (auto v : g.adj[u]) {
    indegree[v] += 1;
    sources.erase(v);
  }
}

int main(int argc, char* argv[]) {

  Graph g = {
    6,
    {
      {},
      {},
      { 3 },
      { 1 },
      { 0, 1 },
      { 0, 2 },
    }
  };

  // Graph g = {
  //   3,
  //   {
  //     {1, 2},
  //     {},p
  //     {},
  //   }
  // };

  tsortPrintAll(g);

  return 0;
}
