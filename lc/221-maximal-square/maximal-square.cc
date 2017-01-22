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
  int maximalSquare(vector<vector<char> >& matrix) {
    int m = matrix.size();
    if (m <= 0) return 0;
    int n = matrix[0].size();
    if (n <= 0) return 0;

    // m >= 1 and n >= 1
    vector<vector<int> > w(m, vector<int>(n, 0));
    // First row
    for (size_t j = 0; j < n; ++j) w[0][j] = matrix[0][j] == '1';
    // First col
    for (size_t i = 0; i < m; ++i) w[i][0] = matrix[i][0] == '1';

    for (size_t i = 1; i < m; ++i) {
      for (size_t j = 1; j < n; ++j) {
        if (matrix[i][j] == '0') {
          w[i][j] = 0;
        } else {
          int w1 = w[i - 1][j];
          int w2 = w[i][j - 1];
          if (w1 == w2) {
            w[i][j] = matrix[i - w1][j - w1] == '1' ? w1 + 1 : w1;
          } else {
            w[i][j] = min(w1, w2) + 1;
          }
        }
      }
    }

    int maxWidth = w[0][0];
    for (size_t i = 0; i < m; ++i)
      for (size_t j = 0; j < n; ++j)
        maxWidth = max(maxWidth, w[i][j]);

    return maxWidth * maxWidth;
  }
};

void test(vector<vector<char> >& matrix) {
  Solution sol;
  cout << "matrix:\n";
  for (auto row : matrix) {
    for (auto col : row) cout << col << " ";
    cout << "\n";
  }
  cout << "result: " << sol.maximalSquare(matrix) << "\n\n";
}

int main(int argc, char* argv[]) {
  {
    vector<vector<char> > m = {
      { '1', '0', '1', '0', '0' },
      { '1', '0', '1', '1', '1' },
      { '1', '1', '1', '1', '1' },
      { '1', '0', '0', '1', '0' }
    };
    test(m);
  }
  {
    vector<vector<char> > m = {
      { '0' }
    };
    test(m);
  }
  {
    vector<vector<char> > m = {
      { '1' }
    };
    test(m);
  }
  {
    vector<vector<char> > m = {
      { '1', '0', '1', '0', '0' },
      { '1', '1', '1', '1', '1' },
      { '1', '1', '1', '1', '1' },
      { '1', '1', '1', '1', '0' }
    };
    test(m);
  }
  {
    vector<vector<char> > m = {
      { '1', '0', '1', '0' },
      { '1', '0', '1', '1' },
      { '1', '0', '1', '1' },
      { '1', '1', '1', '1' }
    };
    test(m);
  }
  return 0;
}
