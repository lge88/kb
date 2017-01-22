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
  // Misra, Jayadev, and David Gries. "Finding repeated elements."
  // Science of computer programming 2.2 (1982): 143-152.
  // http://www.sciencedirect.com/science/article/pii/0167642382900120#
  vector<int> majorityElement(vector<int>& nums) {
    int k = 3, n = nums.size(), d = 0;
    map<int, int> t;
    map<int, int>::iterator it, end = t.end();
    for (int i = 0; i < n; ++i) {
      it = t.find(nums[i]);
      if (it == end) {
        t[nums[i]] = 1;
        ++d;
        if (d == k) {
          // delete k distinct values from t and update d
          it = t.begin();
          while (it != end) {
            map<int, int>::iterator next = it;
            ++next;
            if (it->second <= 1) {
              t.erase(it);
              d--;
            } else {
              it->second--;
            }
            it = next;
          }
        }
      } else {
        it->second++;
      }
    }

    vector<int> res;
    int thres = n / k;
    for (it = t.begin(); it != end; ++it) {
      int candidate = it->first;
      int count = 0;
      for (int i = 0; i < n; ++i) {
        if (nums[i] == candidate) ++count;
      }

      if (count > thres) res.push_back(candidate);
    }
    return res;
  }
};

void test(vector<int>& nums) {
  cout << "nums: [ ";
  for (auto x : nums) cout << x << " ";
  cout << "]\n";

  Solution sol;
  vector<int> res = sol.majorityElement(nums);
  cout << "res: [ ";
  for (auto x : res) cout << x << " ";
  cout << "]\n\n";
}

int main(int argc, char* argv[]) {
  {
    vector<int> nums = { 1, 2, 1, 1, 2, 3 };
    test(nums);
  }
  {
    vector<int> nums = { 1, 2, 1, 2, 3 };
    test(nums);
  }
  {
    vector<int> nums = { 2, 2, 1, 4 };
    test(nums);
  }
  return 0;
}
