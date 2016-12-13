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
#include <cassert>

using namespace std;

class Solution {
 public:
  int wordsTyping(vector<string>& sentence, int rows, int cols) {
    int res = 0;
    int n = sentence.size(), i = 0, x = 0, y = 0;
    while (y < rows) {
      int l = sentence[i].size();
      if (x + l <= cols) {// can fit
        if (x + l + 1 < cols) {
          x = x + l + 1;
        } else {
          x = 0;
          ++y;
        }

        ++i;
        if (i == n) {
          ++res;
          i = 0;
          if (x == 0) {
            return (rows / y) * res + wordsTyping(sentence, rows % y, cols);
          }
        }
      } else {// won't fit
        x = 0;
        ++y;
      }
    }
    return res;
  }
};

void test(vector<string>& sentence, int rows, int cols, int expected) {
  Solution sol;
  cout << "sentence: [";
  for (auto x: sentence) cout << " \"" << x << "\"";
  cout << " ]\n";
  cout << "rows: " << rows << "\n";
  cout << "cols: " << cols << "\n";
  int actual = sol.wordsTyping(sentence, rows, cols);
  cout << "wordsTyping(...): " << actual << ", expected: " << expected << "\n\n";
  assert(actual == expected);
}

int main(int argc, char* argv[]) {
  {
    vector<string> sentence = { "hello", "world" };
    test(sentence, 2, 8, 1);
  }
  {
    vector<string> sentence = { "a", "bcd", "e" };
    test(sentence, 3, 6, 2);
  }
  {
    vector<string> sentence = { "I", "had", "apple", "pie" };
    test(sentence, 4, 5, 1);
  }
  {
    vector<string> sentence = { "a" };
    test(sentence, 20000, 20000, 10000*20000);
  }
  {
    // f-p-a-f
    // p-a-f-p
    // a-f-p-a
    // f-p-a-f
    // p-a-f-p
    // a-f-p-a
    // f-p-a-f
    // p-a-f-p
    vector<string> sentence = { "f", "p", "a" };
    test(sentence, 8, 7, 10);
  }
  {
    // TLE
    vector<string> sentence = { "abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r","abcdef","ghijkl","mnop","qrs","tuv","wxyz","asdf","ogfd","df","r" };
    test(sentence, 20000, 20000, 851000);
  }
  return 0;
}
