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
  int partition(vector<int>& nums, int left, int right) {
    int pivotIndex = left + (right - left) / 2;
    int pivot = nums[pivotIndex];
    swap(nums[pivotIndex], nums[right]);

    int i = left - 1;
    for (int j = left; j <= right; ++j) {
      if (nums[j] <= pivot) {
        ++i;
        swap(nums[i], nums[j]);
      }
    }
    return i;
  }

  int select(vector<int>& nums, int left, int right, int k) {
    int newPivotIndex = partition(nums, left, right);
    int newPivotRank = right - newPivotIndex + 1;
    if (k == newPivotRank) {
      return nums[newPivotIndex];
    } else if (k < newPivotRank) {
      return select(nums, newPivotIndex + 1, right, k);
    } else {
      return select(nums, left, newPivotIndex - 1, k - newPivotRank);
    }
  }

  int findKthLargest(vector<int>& nums, int k) {
    int n = nums.size();
    return select(nums, 0, n - 1, k);
  }
};

void test(vector<int>& nums, int k) {
  Solution sol;
  ostream_iterator<int> oit(cout, " ");
  cout << "nums: ";
  copy(nums.begin(), nums.end(), oit);
  cout << "\n";
  cout << "k: " << k << "\n";
  cout << "result: " << sol.findKthLargest(nums, k) << "\n";
}

int main(int argc, char* argv[]) {
  {
    vector<int> nums = { 3,2,1,5,6,4 };
    int k = 2;
    test(nums, k);
  }
  {
    vector<int> nums = { 3,2,3,1,2,4,5,5,6 };
    int k = 4;
    test(nums, k);
  }
  return 0;
}
