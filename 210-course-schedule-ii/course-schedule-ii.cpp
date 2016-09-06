#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <algorithm>

using namespace std;

class Solution {
 public:
  bool dfsVisit(const vector<pair<int, int> >& g, const int u,
                vector<int>& colors, vector<int>& output) {
    colors[u] = 1;
    for (size_t i = 0; i < g.size(); ++i) {
      const pair<int, int>& item = g[i];
      if (item.second != u) continue;
      int v = item.first;
      if (colors[v] == 0) {
        bool ok = dfsVisit(g, v, colors, output);
        if (!ok) return false;
      } else if (colors[v] == 1) {
        return false;
      }
    }
    colors[u] = 2;
    output.push_back(u);
    return true;
  }

  vector<int> findOrder(int numCourses, vector<pair<int, int> >& prerequisites) {
    vector<int> order;
    vector<int> colors(numCourses, 0);
    for (int i = 0; i < numCourses; ++i) {
      if (colors[i] == 0) {
        bool ok = dfsVisit(prerequisites, i, colors, order);
        if (!ok) return vector<int>(0);
      }
    }
    reverse(order.begin(), order.end());
    return order;
  }
};

void test(int numCourses, vector<pair<int, int> >& prerequisites) {
  std::cout << "numCourses: " << numCourses << "\n";
  for (size_t i = 0; i < prerequisites.size(); ++i) {
    const pair<int, int>& item = prerequisites[i];
    std::cout << item.first << " <- " << item.second << "\n";
  }

  Solution sol;
  vector<int> order = sol.findOrder(numCourses, prerequisites);
  std::cout << "order: [ ";
  for (size_t i = 0; i < order.size(); ++i) {
    std::cout << order[i] << " ";
  }
  std::cout << "]\n";
}

int main(int argc, char* argv[]) {
  {
    int numCourses = 2;
    vector<pair<int, int> > prerequisites = { pair<int, int>(1, 0) };
    test(numCourses, prerequisites);
  }
  {
    int numCourses = 4;
    vector<pair<int, int> > prerequisites = {
      pair<int, int>(1, 0),
      pair<int, int>(2, 0),
      pair<int, int>(3, 1),
      pair<int, int>(3, 2),
    };
    test(numCourses, prerequisites);
  }
  return 0;
}
