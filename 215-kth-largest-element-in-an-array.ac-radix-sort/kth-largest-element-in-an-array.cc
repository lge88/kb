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
  void radixSort(vector<int>& nums) {
    size_t n = nums.size();
    vector<int> zerosBucket;
    vector<int> onesBucket;

    for (size_t i = 0; i < 32; ++i) {
      zerosBucket.clear();
      onesBucket.clear();
      for (size_t j = 0; j < n; ++j) {
        int num = nums[j];
        if (num & (1 << i)) {
          onesBucket.push_back(num);
        } else {
          zerosBucket.push_back(num);
        }
      }

      if (i == 31) {
        copy(onesBucket.begin(), onesBucket.end(), nums.begin());
        copy(zerosBucket.begin(), zerosBucket.end(), nums.begin() + onesBucket.size());
      } else {
        copy(zerosBucket.begin(), zerosBucket.end(), nums.begin());
        copy(onesBucket.begin(), onesBucket.end(), nums.begin() + zerosBucket.size());
      }
    }
  }

  int findKthLargest(vector<int>& nums, int k) {
    radixSort(nums);
    return nums[nums.size() - k];
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
  {
    vector<int> nums = { 4, 5, 6, -3, -1, 0, -4 };
    int k = 4;
    test(nums, k);
  }
  return 0;
}
