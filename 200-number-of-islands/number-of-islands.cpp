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

  void explore(const vector<vector<char> >& grid, size_t i, size_t j, vector<vector<bool> >& visited) {
    visited[i][j] = true;

    if (i + 1 < grid.size() && grid[i + 1][j] == '1' && visited[i + 1][j] == false) {
      explore(grid, i + 1, j, visited);
    }

    if (i >= 1 && grid[i - 1][j] == '1' && visited[i - 1][j] == false) {
      explore(grid, i - 1, j, visited);
    }

    if (j + 1 < grid[i].size() && grid[i][j + 1] == '1' && visited[i][j + 1] == false) {
      explore(grid, i, j + 1, visited);
    }

    if (j >= 1 && grid[i][j - 1] == '1' && visited[i][j - 1] == false) {
      explore(grid, i, j - 1, visited);
    }
  }

  int numIslands(vector<vector<char> >& grid) {
    int m = grid.size();
    if (m <= 0) return 0;
    int n = grid[0].size();
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    int count = 0;

    for (size_t i = 0; i < grid.size(); ++i) {
      for (size_t j = 0; j < grid[i].size(); ++j) {
        if (visited[i][j] == false && grid[i][j] == '1') {
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
