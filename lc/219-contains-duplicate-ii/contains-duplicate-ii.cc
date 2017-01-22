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
  bool containsNearbyDuplicate(vector<int>& nums, int k) {
    // num => largest index in nums where its value is num
    unordered_map<int, int> seen;
    int n = nums.size();
    for (int i = 0; i < n; ++i) {
      int num = nums[i];
      if (seen.find(num) == seen.end()) {
        seen[num] = i;
      } else {
        if (i - seen[num] <= k) return true;
        seen[num] = i;
      }
    }
    return false;
  }
};

void test(vector<int>& nums, int k) {
  Solution sol;
  cout << "\nnums: [ ";
  for (size_t i = 0; i < nums.size(); ++i)
    cout << (i > 0 ? ", " : "") << nums[i];
  cout << " ]\n";
  cout << "k: " << k << "\n";
  cout << "result: " << sol.containsNearbyDuplicate(nums, k) << "\n";
}

int main(int argc, char* argv[]) {
  {
    vector<int> nums = { 1, 2, 3, 4, 7, 6 };
    int k = 5;
    test(nums, k);
  }
  {
    vector<int> nums = { 1, 2, 3, 4, 1, 7, 6 };
    int k = 5;
    test(nums, k);
  }
  {
    vector<int> nums = { 1, 2, 3, 4, 1, 7, 6 };
    int k = 3;
    test(nums, k);
  }
  return 0;
}
