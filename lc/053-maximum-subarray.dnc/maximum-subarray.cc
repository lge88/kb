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
  int maxSubArrayDQ(vector<int>& nums, int start, int end) {
    if (start >= end) return nums[start];

    int mid = start + (end - start) / 2;
    int maxLeft = maxSubArrayDQ(nums, start, mid);
    int maxRight = maxSubArrayDQ(nums, mid + 1, end);

    int sumLeft = nums[mid], maxCrossLeft = sumLeft;
    for (int i = mid - 1; i >= 0; --i) {
      sumLeft += nums[i];
      maxCrossLeft = max(maxCrossLeft, sumLeft);
    }

    int sumRight = nums[mid + 1], maxCrossRight = sumRight;
    for (int i = mid + 2; i <= end; ++i) {
      sumRight += nums[i];
      maxCrossRight = max(maxCrossRight, sumRight);
    }

    return max(max(maxLeft, maxRight), maxCrossLeft + maxCrossRight);
  }

  int maxSubArray(vector<int>& nums) {
    return maxSubArrayDQ(nums, 0, nums.size() - 1);
  }
};

void test(vector<int>& nums) {
  Solution sol;
  cout << "nums:";
  for (auto x: nums) cout << " " << x;
  cout << "\n";
  cout << "max subarray sum: " << sol.maxSubArray(nums) << "\n";
}

int main(int argc, char* argv[]) {
  {
    vector<int> nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
    test(nums);
  }
  return 0;
}
