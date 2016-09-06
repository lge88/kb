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
  bool detectCycle(const vector<pair<int, int> >& prerequisites, int u, vector<int>& colors) {
    colors[u] = 1;

    for (size_t i = 0; i < prerequisites.size(); ++i) {
      const pair<int, int>& item = prerequisites[i];
      if (item.second != u) continue;

      int v = item.first;
      if (colors[v] == 0) {
        bool hasCycle = detectCycle(prerequisites, v, colors);
        if (hasCycle) return true;
      } else if (colors[v] == 1) {
        return true;
      }
    }

    colors[u] = 2;
    return false;
  }

  // All courses can be finished if any only if the dependency graph is acyclic
  bool canFinish(int numCourses, vector<pair<int, int> >& prerequisites) {
    // 0 - white, 1 - gray, 2 - black
    vector<int> colors(numCourses, 0);
    for (size_t i = 0; i < numCourses; ++i) {
      if (colors[i] == 0) {
        bool hasCycle = detectCycle(prerequisites, i, colors);
        if (hasCycle) return false;
      }
    }
    return true;
  }
};

void test(int numCourses, vector<pair<int, int> >& prerequisites) {
  std::cout << "numCourses: " << numCourses << "\n";
  for (size_t i = 0; i < prerequisites.size(); ++i) {
    const pair<int, int>& item = prerequisites[i];
    std::cout << item.first << " <- " << item.second << "\n";
  }

  Solution sol;
  std::cout << "canFinish: " << sol.canFinish(numCourses, prerequisites) << "\n";
}

int main(int argc, char* argv[]) {

  {
    int numCourses = 2;
    vector<pair<int, int> > deps(1, pair<int, int>(1, 0));
    test(numCourses, deps);
  }

  return 0;
}
