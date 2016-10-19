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
  int solve(int x) {
    return x;
  }
};

void test(int x) {
  Solution sol;
  cout << "x: " << x << "\n";
  cout << "result: " << sol.solve(x) << "\n";
}

int main(int argc, char* argv[]) {
  {
    int x = 42;
    test(x);
  }
  return 0;
}
