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
  vector<string> summaryRanges(vector<int>& nums) {
    vector<string> res;
    size_t n = nums.size();
    if (n == 0) return res;

    size_t start = 0, end = 0;
    ostringstream oss;
    for (size_t i = 1; i < n; ++i) {
      if (nums[end] + 1 == nums[i]) {
        ++end;
      } else {
        oss.str("");
        if (nums[start] == nums[end]) {
          oss << nums[start];
        } else {
          oss << nums[start] << "->" << nums[end];
        }
        res.push_back(oss.str());
        start = i;
        end = i;
      }
    }
    oss.str("");
    if (nums[start] == nums[end]) {
      oss << nums[start];
    } else {
      oss << nums[start] << "->" << nums[end];
    }
    res.push_back(oss.str());
    return res;
  }
};

void test(vector<int>& nums) {
  Solution sol;
  cout << "nums: [ ";
  for (auto x : nums) cout << x << ", ";
  cout << "]\n";

  cout << "result: [ ";
  vector<string> res = sol.summaryRanges(nums);
  for (auto x : res) cout << "\"" << x << "\", ";
  cout << "]\n";
}

int main(int argc, char* argv[]) {
  {
    vector<int> nums = { 0, 1, 2, 4, 5, 7 };
    test(nums);
  }
  {
    vector<int> nums = { 0, 1, 2, 4, 7 };
    test(nums);
  }
  {
    vector<int> nums = { 0, 1, 2, 3, 7, 8, 9, 10, 15, 16 };
    test(nums);
  }
  return 0;
}
