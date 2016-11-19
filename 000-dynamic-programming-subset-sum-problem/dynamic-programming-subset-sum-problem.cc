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

bool dfs(const vector<int>& arr, int start, int target) {
  int n = arr.size();
  if (start >= n) return target == 0;

  // 0 <= start < n
  return dfs(arr, start + 1, target) || dfs(arr, start + 1, target - arr[start]);
}

bool containsSubsetSumEquals(const vector<int>& arr, int target) {
  // dfs solution results in 2^n complexity
  // return dfs(arr, 0, target);

  if (target == 0) return true;
  // target > 0
  int n = arr.size();
  if (n == 0) return false;

  // vector<vector<bool> > F(n, vector<bool>(target + 1, false));

  // HUGE performance improvement by using following. How does this
  // even work? Does it get allocated in heap? Why it doesn't need
  // `new' keyword.
  bool F[n][target+1];

  // boundary conditions
  for (int i = 0; i < n; ++i) F[i][0] = false;
  for (int i = 0; i <= target; ++i) F[0][i] = i == arr[0];

  for (int x = 1; x < n; ++x) {
    for (int y = 1; y <= target; ++y) {
      if (F[x-1][y]) {
        F[x][y] = true;
        continue;
      }

      int newTarget = y - arr[x];
      if (newTarget < 0) {
        F[x][y] = false;
        continue;
      }
      // newTarget > 0
      F[x][y] = F[x-1][newTarget];
    }
  }

  return F[n-1][target];
}

bool containsEqualSubsetSum(const vector<int>& arr) {
  int total = 0;
  for (int i = 0; i < arr.size(); ++i) total += arr[i];
  if (total % 2 != 0) return false;
  return containsSubsetSumEquals(arr, total / 2);
}

int main() {
  int numTestCases;
  cin >> numTestCases;
  for (int i = 0; i < numTestCases; ++i) {
    int len;
    vector<int> arr;
    cin >> len;
    arr.resize(len);
    for (int j = 0; j < len; ++j) cin >> arr[j];

    cout << (containsEqualSubsetSum(arr) ? "YES" : "NO") << "\n";
  }

  return 0;
}
