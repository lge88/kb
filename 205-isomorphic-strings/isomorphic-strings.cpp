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
  bool isIsomorphic(string s, string t) {
    if (s.size() != t.size()) return false;

    unordered_map<char, char> dict;
    unordered_set<char> valSet;
    size_t len = s.size();

    for (size_t i = 0; i < len; ++i) {
      char cs = s[i];
      char ct = t[i];
      unordered_map<char, char>::const_iterator it = dict.find(cs);

      if (it == dict.end()) {
        dict[cs] = ct;
        if (valSet.find(ct) != valSet.end()) return false;
        valSet.insert(ct);
      } else {
        if (it->second != ct) return false;
      }
    }

    return true;
  }
};

void test(string s, string t) {
  Solution sol;
  cout << "s: " << s << "\n";
  cout << "t: " << t << "\n";
  cout << "isIsomorphic(s, t): " << sol.isIsomorphic(s, t) << "\n";
}

int main(int argc, char* argv[]) {
  test("egg", "add");
  test("foo", "bar");
  test("paper", "title");
  test("ab", "aa");
  return 0;
}
