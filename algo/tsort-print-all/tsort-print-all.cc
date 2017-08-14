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

void dfs(int u, const Graph& g, vector<int>& indegree, vector<int>& path, const set<int>& sources);

void tsortPrintAll(const Graph& g) {
  int n = g.V;
  vector<int> indegree(n, 0);
  for (auto edge : g.adj) {
    for (auto v : edge) {
      indegree[v] += 1;
    }
  }

  set<int> sources;
  for (int u = 0; u < n; ++u) {
    if (indegree[u] == 0) sources.insert(u);
  }

  vector<int> path;
  for (auto u : sources) {
    path.push_back(u);

    auto newSources(sources);
    newSources.erase(u);
    dfs(u, g, indegree, path, newSources);

    path.pop_back();
  }
}

void dfs(int u, const Graph& g, vector<int>& indegree, vector<int>& path, const set<int>& sources) {
  if (path.size() == g.V) {
    cout << "[";
    for (auto u : path) cout << " " << u;
    cout << " ]\n";
    return;
  }

  auto sourcesCopy(sources);
  for (auto v : g.adj[u]) {
    indegree[v] -= 1;
    if (indegree[v] == 0) sourcesCopy.insert(v);
  }

  for (auto v : sourcesCopy) {
    path.push_back(v);

    auto newSources(sourcesCopy);
    newSources.erase(v);
    dfs(v, g, indegree, path, newSources);

    path.pop_back();
  }

  for (auto v : g.adj[u]) {
    indegree[v] += 1;
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
