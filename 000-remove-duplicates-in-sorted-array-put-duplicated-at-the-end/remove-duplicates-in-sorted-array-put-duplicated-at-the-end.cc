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
  int removeDuplicates(string& s) {
    int len = s.size();
    if (len <= 1) return len;

    int tail = 0;
    for (int head = 1; head < len; ++head) {
      if (s[head] != s[tail]) {
        swap(s[tail+1], s[head]);
        ++tail;
      }
    }
    return tail + 1;
  }
};

void test(string x) {
  Solution sol;
  cout << "x: " << x << "\n";
  const int len = sol.removeDuplicates(x);
  cout << "result: " << x.substr(0, len) << " " << x.substr(len) << "\n";
  cout << "len: " << len << "\n";
}

int main(int argc, char* argv[]) {

  test("abccdeeefg");
  // Expected: 7, "abcdefg ..."

  test("abccdeeeefgggg");
  // Expected: 7, "abcdefg ..."

  test("abcdfh");
  // Expected: 6, "abcdfh ..."

  test("");
  // Expected: 0, ""

  test("a");
  // Expected: 1, "a .."

  return 0;
}
