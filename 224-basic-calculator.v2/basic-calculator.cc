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
  int calculate(string s) {
    int n = s.size();
    int result = 0;
    int sign = 1;
    vector<pair<int, int> > stack;
    for (size_t i = 0; i < n; ++i) {
      char c = s[i];
      if (c >= '0' && c <= '9') {
        int num = c - '0';
        int j = i + 1;
        while (j < n && s[j] >= '0' && s[j] <= '9') {
          num = num * 10 + (s[j] - '0');
          ++j;
        }
        i = j - 1;
        result += sign * num;
      }
      else if (c == '+') {
        sign = 1;
      }
      else if (c == '-') {
        sign = -1;
      }
      else if (c == '(') {
        stack.push_back(make_pair(result, sign));
        result = 0;
        sign = 1;
      }
      else if (c == ')') {
        const pair<int, int>& top = stack.back();
        result = result * top.second + top.first;
        stack.pop_back();
      }
    }
    return result;
  }
};

void test(const string& input, int expected) {
  Solution sol;
  cout << "input: \"" << input << "\"\n";
  cout << "result: " << sol.calculate(input) << "\n";
  cout << "expected: " << expected << "\n\n";
}

int main(int argc, char* argv[]) {
  test("1 + 1", 2);
  test(" 2-1 + 2 ", 3);
  test("(1+(4+5+2)-3)+(6+8)", 23);
  return 0;
}
