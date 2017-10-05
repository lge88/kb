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

void printVec(const string& name, const vector<int>& A) {
  cout << name <<  ": [";
  for (auto x : A) cout << " " << x;
  cout << " ]\n";
}

class Solution {
 public:
  int findNumberOfLIS(vector<int>& nums) {
    int n = nums.size();
    if (n == 0) return 0;
    // F[i] - number of LIS that ends at nums[i]
    // G[i] - length of LIS that ends at nums[i]
    vector<int> F(n, 1), G(n, 1);
    for (int i = 1; i < n; ++i) {
      int lenLISBefore = -1;
      for (int j = 0; j < i; ++j) {
        if (nums[j] < nums[i]) {
          lenLISBefore = max(G[j], lenLISBefore);
        }
      }
      int count = 0;
      for (int j = 0; j < i; ++j) {
        if (nums[j] < nums[i] && G[j] == lenLISBefore) {
          count += F[j];
        }
      }
      G[i] = lenLISBefore == -1 ? 1 : lenLISBefore + 1;
      F[i] = lenLISBefore == -1 ? 1 : count;
    }
    printVec("F", F);
    printVec("G", G);
    int maxLen = *max_element(G.begin(), G.end());
    int res = 0;
    for (int i = 0; i < n; ++i) res += G[i] == maxLen ? F[i] : 0;
    return res;
  }
};

void test(vector<int> nums) {
  printVec("A", nums);

  Solution sol;
  auto res = sol.findNumberOfLIS(nums);

  cout << "res: " << res << "\n";
}

int main(int argc, char* argv[]) {

  test({1,2,4,3,5,4,7,2});

  return 0;
}
