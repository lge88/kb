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
  string reverseString(string s) {
    if (s.size() == 0) return s;
    size_t i = 0, j = s.size() - 1;
    while (i < j) {
      char tmp = s[i];
      s[i] = s[j];
      s[j] = tmp;
      ++i;
      --j;
    }
    return s;
  }
};

void test(string s) {
  Solution sol;
  cout << "s: " << s << "\n";
  cout << "reverse(s): " << sol.reverseString(s) << "\n";
}

int main(int argc, char* argv[]) {
  {
    string x = "hello";
    test(x);
  }
  return 0;
}
