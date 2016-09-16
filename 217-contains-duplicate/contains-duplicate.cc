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
  bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for (size_t i = 0; i < nums.size(); ++i) {
      if (seen.find(nums[i]) != seen.end()) return true;
      seen.insert(nums[i]);
    }
    return false;
  }
};

void test(vector<int>& nums) {
  Solution sol;
  cout << "nums: [ ";
  for (size_t i = 0; i < nums.size(); ++i)
    cout << (i > 0 ? ", " : "") << nums[i];
  cout << " ]\n";
  cout << "result: " << sol.containsDuplicate(nums) << "\n";
}

int main(int argc, char* argv[]) {
  {
    vector<int> nums { 1, 2, 3, 3 };
    test(nums);
  }
  {
    vector<int> nums { 1, 2, 3, 4 };
    test(nums);
  }
  return 0;
}
