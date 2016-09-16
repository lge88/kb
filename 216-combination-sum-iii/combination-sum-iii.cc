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
  void combinationSum3Helper(
      int k,
      int n,
      int sumSofar,
      set<int>& path,
      vector<vector<int> >& result) {
    if (path.size() > k) return;
    if (path.size() == k) {
      if (sumSofar == n) {
        result.push_back(vector<int>(path.begin(), path.end()));
        return;
      }
      return;
    }

    if (sumSofar >= n) return;

    for (int i = 0; i <= 9; ++i) {
      if (path.empty() || i < (*path.begin())) {
        path.insert(i);
        combinationSum3Helper(k, n, sumSofar + i, path, result);
        path.erase(i);
      }
    }
  }

  vector<vector<int> > combinationSum3(int k, int n) {
    vector<vector<int> > result;
    set<int> path;
    combinationSum3Helper(k, n, 0, path, result);
    return result;
  }
};

void test(int k, int n) {
  Solution sol;
  cout << "k: " << k << ", n: " << n << "\n";
  cout << "result: [ ";
  const vector<vector<int> > res = sol.combinationSum3(k, n);
  for (size_t i = 0; i < res.size(); ++i) {
    if (i > 0) cout << ", ";
    cout << "[";
    for (size_t j = 0; j < res[i].size(); ++j) {
      cout << (j > 0 ? ", " : "") << res[i][j];
    }
    cout << "]";
  }
  cout << " ]\n";
}

int main(int argc, char* argv[]) {

  // test(0, 2);
  // test(1, 2);
  test(3, 7);
  test(3, 9);

  return 0;
}
