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
  int robNoCircle(vector<int>& nums, size_t from, size_t to) {
    if (to < from) return 0;
    size_t n = to - from + 1;
    if (n == 1) return nums[from];
    if (n == 2) return max(nums[from], nums[from + 1]);

    int a = nums[from], b = max(a, nums[from + 1]);
    int c = 0;
    for (size_t i = 2; i < n; ++i) {
      c = max(a + nums[from + i], b);
      a = b;
      b = c;
    }
    return c;
  }

  int rob(vector<int>& nums) {
    size_t n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return max(nums[0], nums[1]);
    int a = robNoCircle(nums, 0, n - 2);
    int b = robNoCircle(nums, 1, n - 3);
    return max(a, b + nums[n - 1]);
  }
};

void test(vector<int>& nums) {
  Solution sol;
  cout << "nums: [ ";
  for (size_t i = 0; i < nums.size(); ++i)
    cout << (i > 0 ? ", " : "") << nums[i];
  cout << " ]\n";
  cout << "rob: " << sol.rob(nums) << "\n";
}

int main(int argc, char* argv[]) {
  {
    vector<int> nums = { 5, 2, 4, 7, 1, 2 };
    test(nums);
  }
  {
    vector<int> nums = { 2, 1, 1, 2 };
    test(nums);
  }
  {
    vector<int> nums = { 6, 6, 4, 8, 4, 3, 3, 10 };
    test(nums);
  }
  return 0;
}
