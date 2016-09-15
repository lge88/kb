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
  char findTheDifference(string s, string t) {
    size_t freqS[26];
    size_t freqT[26];
    for (size_t i = 0; i < 26; ++i) {
      freqS[i] = 0;
      freqT[i] = 0;
    }

    for (size_t i = 0; i < s.size(); ++i) freqS[s[i] - 'a'] += 1;
    for (size_t i = 0; i < t.size(); ++i) freqT[t[i] - 'a'] += 1;
    char result = 'a';
    while (result != 'z') {
      if (freqS[result - 'a'] != freqT[result - 'a']) break;
      result += 1;
    }
    return result;
  }
};

void test(string s, string t) {
  Solution sol;
  cout << "s: " << s << "\n";
  cout << "t: " << t << "\n";
  cout << "result: " << sol.findTheDifference(s, t) << "\n";
}

int main(int argc, char* argv[]) {

  test("abcd", "cxbad");
  test("aabbc", "fcbaba");

  return 0;
}
