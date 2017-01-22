#include <iostream>
#include <string>
#include <vector>
#include <iterator>

using namespace std;

class Solution {
 public:
  int lengthLongestPath(string input) {
    vector<int> parentLens;
    int itemLen = 0;
    int level = 0;
    int sofar = 0;
    bool isFile = false;

    for (size_t i = 0; i < input.size(); ++i) {
      char c = input[i];
      if (c != '\n' && c != '\t') {
        while (parentLens.size() > level) parentLens.pop_back();
        ++itemLen;
        if (c == '.') isFile = true;
      }

      if (c == '\t') ++level;

      if (c == '\n' || i + 1 == input.size()) {
        int parentLen = parentLens.empty() ? 0 : parentLens.back();
        int currentLen = parentLen + itemLen;

        if (isFile)
          sofar = max(sofar, currentLen);

        parentLens.push_back(currentLen + 1);
        itemLen = 0;
        level = 0;
        isFile = false;
      }
    }
    return sofar;
  }
};

int main() {
  std::istreambuf_iterator<char> it(std::cin);
  std::istreambuf_iterator<char> end = std::istreambuf_iterator<char>();
  Solution sol;
  int result = sol.lengthLongestPath(std::string(it, end));
  std::cout << "result: " << result << "\n";
  return 0;
}
