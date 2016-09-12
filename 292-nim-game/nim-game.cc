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
  bool canWinNim(int x) {
    return x % 4;
  }
};

void test(int x) {
  Solution sol;
  cout << "x: " << x << "\n";
  cout << "result: " << sol.canWinNim(x) << "\n";
}

int main(int argc, char* argv[]) {
  {
    int x = 42;
    test(x);
  }
  {
    int x = 1348820612;
    test(x);
  }
  return 0;
}
