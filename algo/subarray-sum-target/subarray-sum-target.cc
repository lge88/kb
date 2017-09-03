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
#include <utility>

using namespace std;

// All non-negative number
pair<int, int> subarraySum2(const vector<int>& A, int target) {
  auto res = pair<int, int>(-1, -1);
  int n = A.size();
  if (n == 0) return res;

  int i = 0, j = -1, sum = 0;
  while (j < n) {
    // move j to until sum([i..j]) > target
    while (j < n) {
      j += 1;
      sum += A[j];
      if (sum == target) return { i, j };
      else if (sum > target) break;
    }

    // sum > target or j == n
    // move i until sum([i..j]) < target
    while (sum > target) {
      sum -= A[i];
      i += 1;
      if (sum == target) return { i, j };
    }
  }

  return { -1, -1 };
}

pair<int, int> subarraySum1(const vector<int>& A, int target) {
  auto res = pair<int, int>(-1, -1);
  int n = A.size();
  if (n == 0) return res;

  int j = 0, sum = A[0];
  for (int i = 0; i < n; i++) {
    while (j < n && sum <= target) {
      // sum is sum([i, j])
      if (sum == target) {
        return { i, j };
      }
      else {
        j += 1;
        if (j < n) {
          sum += A[j];
        }
      }
    }
    sum -= A[i];
  }

  return res;
}

pair<int, int> subarraySum(const vector<int>& A, int target) {
  int n = A.size();
  if (n == 0) return { -1, -1 };

  int j = 0, sum = A[0];
  for (int i = 0; i < n; ++i) {
    // sum == sum(A[i..j])
    // Find first j such that sum(A[i..j]) >= target
    while (j + 1 < n && sum < target) {
      j = j + 1;
      sum += A[j];
    }

    if (sum == target) {
      return { i, j };
    }
    // No such j exist, return immediately. Not required, but faster.
    else if (sum < target) {
      return { -1, -1 };
    }

    // sum > target
    sum -= A[i];
  }

  return { -1, -1 };
}

// Handle negative numbers as well
pair<int, int> subarraySumWithNeg(const vector<int>& A, int target) {
  unordered_map<int, int> seen;
  int n = A.size();
  int sum = 0;
  for (int i = 0; i < n; ++i) {
    sum += A[i];
    // sum == sum(A[0..i]);
    int x = sum - target;
    if (x == 0) {
      return { 0, i };
    }
    else if (seen.find(x) != seen.end()) {
      return { seen[x] + 1, i };
    }
    seen[sum] = i;
  }
  return { -1, -1 };
}


void test(const vector<int>& A, int target) {
  cout << "target: " << target << "\n";
  cout << "A: [";
  for (auto x : A) cout << " " << x;
  cout << " ]\n";

  cout << "res: ";
  // auto res = subarraySum(A, target);
  auto res = subarraySumWithNeg(A, target);
  if (res.first != -1) {
    cout << "[ " << res.first << ", " << res.second << " ]\n";
  } else {
    cout << "NULL\n";
  }
  cout << "\n";
}

int main(int argc, char* argv[]) {
  test({ 2, 1, 3, 5, 0 }, 8);
  test({ 2, 1, 3, 5, 2 }, 18);
  test({ 2, 1, 3, 5, 2 }, 13);
  test({ 2, 1, 3, 5, 2 }, 1);
  test({ 2, 1, 3, 5, 2 }, 5);
  test({ 2, 1, 3, 5, 2 }, 10);

  test({ 2, -1, -3, 5, 2 }, -4);
  return 0;
}
