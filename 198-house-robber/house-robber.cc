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
  // F(x) = max(F(x-2) + nums[x], F(x-1))
  // Want: F(nums.size() - 1)
  int rob(vector<int>& nums) {
    size_t n = nums.size();
    if (n == 0) return 0;
    if (n == 1) return nums[0];
    if (n == 2) return max(nums[0], nums[1]);

    int a = nums[0], b = max(a, nums[1]);
    int c = 0;
    for (size_t i = 2; i < n; ++i) {
      c = max(a + nums[i], b);
      a = b;
      b = c;
    }
    return c;
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
    vector<int> nums = { 6, 4, 8, 4, 3 };
    test(nums);
  }
  return 0;
}
