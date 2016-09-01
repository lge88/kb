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

  void explore(const vector<vector<char> >& grid, size_t i, size_t j, unordered_set<string>& visited) {
    stringstream oss;
    oss << i << "_" << j;
    visited.insert(oss.str());

    oss.str(""); oss << (i + 1) << "_" << j;
    if (i + 1 < grid.size() && grid[i + 1][j] == '1' && visited.find(oss.str()) == visited.end()) {
      explore(grid, i + 1, j, visited);
    }

    oss.str(""); oss << (i - 1) << "_" << j;
    if (i >= 1 && grid[i - 1][j] == '1' && visited.find(oss.str()) == visited.end()) {
      explore(grid, i - 1, j, visited);
    }

    oss.str(""); oss << i << "_" << j + 1;
    if (j + 1 < grid[i].size() && grid[i][j + 1] == '1' && visited.find(oss.str()) == visited.end()) {
      explore(grid, i, j + 1, visited);
    }

    oss.str(""); oss << i << "_" << j - 1;
    if (j >= 1 && grid[i][j - 1] == '1' && visited.find(oss.str()) == visited.end()) {
      explore(grid, i, j - 1, visited);
    }
  }

  int numIslands(vector<vector<char> >& grid) {

    unordered_set<string> visited;
    stringstream oss;
    int count = 0;

    for (size_t i = 0; i < grid.size(); ++i) {
      for (size_t j = 0; j < grid[i].size(); ++j) {
        oss.str(""); oss << i << "_" << j;
        if (visited.find(oss.str()) == visited.end() && grid[i][j] == '1') {
          explore(grid, i, j, visited);
          ++count;
        }
      }
    }

    return count;
  }
};

void printGrid(const vector<vector<char> >& grid, ostream& to) {
  for (size_t i = 0; i < grid.size(); ++i) {
    for (size_t j = 0; j < grid[i].size(); ++j) {
      to << grid[i][j];
    }
    to << "\n";
  }
}

int main(int argc, char* argv[]) {
  Solution sol;

  vector<vector<char> > g1 {
    { '1', '1', '1', '1', '0' },
    { '1', '1', '0', '1', '0' },
    { '1', '1', '0', '0', '0' },
    { '0', '0', '0', '0', '0' }
  };
  printGrid(g1, cout);
  cout << "num islands: " << sol.numIslands(g1) << "\n";

  vector<vector<char> > g2 {
    { '1', '1', '0', '0', '0' },
    { '1', '1', '0', '0', '0' },
    { '0', '0', '1', '0', '0' },
    { '0', '0', '0', '1', '1' }
  };
  printGrid(g2, cout);
  cout << "num islands: " << sol.numIslands(g2) << "\n";

  return 0;
}
