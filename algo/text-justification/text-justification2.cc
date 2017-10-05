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
  string adjustLine(const vector<string>& words, int start, int end, int extraSpaces) {
    int slots = end - start;
    if (slots == 0) {
      return words[start] + string(extraSpaces, ' ');
    }

    // slots > 0
    string line;
    int base = extraSpaces / slots, remains = extraSpaces % slots;
    for (int j = start; j <= end; ++j) {
      if (j > start) {
        int numSpaces = 1 + base;
        if (remains > 0) {
          numSpaces += 1;
          remains -= 1;
        }
        line += string(numSpaces, ' ');
      }
      line += words[j];
    }
    return line;
  }

  string leftAdjust(const vector<string>& words, int maxWidth, int start, int end) {
    string line;
    for (int j = start; j <= end; ++j) {
      if (j > start) line += ' ';
      line += words[j];
    }
    line += string(maxWidth - line.size(), ' ');
    return line;
  }

  vector<string> fullJustify(vector<string>& words, int maxWidth) {
    vector<string> res;
    int n = words.size();
    // start / end word index of current line
    int start = -1, end = -1;
    // length of current line using left adjust
    int len = 0;
    for (int i = 0; i < n;) {
      int wl = words[i].size();
      int newLen = len == 0 ? wl : len + wl + 1;

      if (newLen <= maxWidth) {
        // word[i] can be added to this line, so do it
        len = newLen;
        if (start == -1) {
          start = i;
          end = i;
        } else {
          end = i;
        }
        i += 1;

        if (newLen < maxWidth) continue;
      }

      // Output adjusted text
      int extraSpaces = maxWidth - len;
      res.push_back(adjustLine(words, start, end, extraSpaces));

      // clear state after output
      len = 0;
      start = -1;
      end = -1;
    }

    // Last line left just
    if (start != -1) {
      res.push_back(leftAdjust(words, maxWidth, start, end));
    }
    return res;
  }
};

void test(vector<string> words, int maxWidth) {
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
  test({"a"}, 1);
  test({"Listen","to","many,","speak","to","a","few."}, 6);
  test({"This", "is", "an", "example", "of", "text", "justification."}, 16);
}
