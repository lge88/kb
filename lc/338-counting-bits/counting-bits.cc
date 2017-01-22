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
  vector<int> countBits(int num) {
    vector<int> result(num + 1, 0);
    for (size_t i = 1; i <= num; ++i) {
      result[i] = result[i >> 1] + (i & 0x00000001);
    }
    return result;
  }
};

void test(int num) {
  Solution sol;
  std::cout << "num: " << num << "\n";
  const vector<int> result = sol.countBits(num);
  std::cout << "result:\n";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << "i: " << i << " -> " << result[i] << "\n";
  }
}

int main(int argc, char* argv[]) {
  {
    int num = 10;
    test(num);
  }
  return 0;
}
