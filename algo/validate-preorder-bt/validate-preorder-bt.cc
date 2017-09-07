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
#include <stack>

using namespace std;

bool isValidSerialization(string preorder) {
  // Items in the stack: 0 - both of its children is not visited, 1 - left is visited, 2 - done
  stack<int> stk;
  string token;
  istringstream from(preorder);
  const char sep = ',';
  const string nil = "#";
  bool first = true;
  while (getline(from, token, sep)) {
    cout << "'" << token << "', first: " << first << ", stk.size(): " << stk.size() << "\n";
    if (!first && stk.empty()) return false;

    first = false;
    if (token != nil) {
      stk.push(0);
    } else {
      // First token is nil
      if (stk.empty()) continue;
      stk.top() += 1;
      while (stk.top() > 1) {
        stk.pop();
        if (stk.empty()) break;
        stk.top() += 1;
      }
    }
  }
  return stk.empty();
}

void test(string input) {
  cout << "input: '" << input << "'\n";
  cout << "res: " << isValidSerialization(input) << "\n";
}

int main(int argc, char* argv[]) {

  test("1,#,#,1");

  return 0;
}
