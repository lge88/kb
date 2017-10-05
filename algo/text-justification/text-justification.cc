#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  string leftAdjust(const vector<string>& words, int start, int end, int spaces) {
    string res;
    for (int i = start; i <= end; ++i) {
      if (i > start) res += " ";
      res += words[i];
    }
    return res + string(spaces, ' ');
  }

  string adjustLine(const vector<string>& words, int start, int end, int spaces) {
    int slots = end - start;
    if (slots == 0) return words[start] + string(spaces, ' ');

    string res;
    int base = spaces / slots, remains = spaces % slots;
    for (int i = start; i <= end; ++i) {
      if (i > start) {
        int numSpaces = 1 + base;
        if (remains > 0) {
          numSpaces += 1;
          remains -= 1;
        }
        res += string(numSpaces, ' ');
      }
      res += words[i];
    }
    return res;
  }

  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    int i = 0, n = words.size();
    vector<string> res;
    while (i < n) {
      int len = 0, j = i;
      int nextLen = words[j].size();
      while (nextLen <= maxWidth) {
        len = nextLen;
        j += 1;
        if (j == n) break;
        nextLen = len + 1 + words[j].size();
      }
      // words[i, j) is fitted in current line
      // j == n or nextLen > maxWidth

      int spaces = maxWidth - len;
      // last line left adjust
      if (j == n) {
        res.push_back(leftAdjust(words, i, j - 1, spaces));
      }
      else {
        res.push_back(adjustLine(words, i, j - 1, spaces));
      }

      i = j;
    }

    return res;
  }
};

void test(vector<string> words, int maxWidth) {
  cout << "maxWidth: " << maxWidth << "\n";
  cout << "input: [ ";
  for (int i = 0, n = words.size(); i < n; ++i) {
    if (i > 0) cout << ", ";
    cout << "'" << words[i] << "'";
  }
  cout << " ]\n";

  Solution sol;
  auto res = sol.fullJustify(words, maxWidth);
  cout << "output:\n";
  for (const auto& x : res) cout << "'" << x << "'\n";
  cout << "\n";
}

int main(int argc, char* argv[]) {
  test({"a"}, 3);
  // test({"Listen","to","many,","speak","to","a","few."}, 6);
  // test({"This", "is", "an", "example", "of", "text", "justification."}, 16);
  test({"a", "b", "c", "d", "e"}, 3);
}
