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
#include <cctype>

using namespace std;

bool checkPartOfWord(const char c) {
  return !isspace(c);
}

int wordCount(const string& input) {
  int count = 0;
  // whether previous char is part of word or not
  bool wasPartOfWord = false;
  for (auto c : input) {
    bool isPartOfWord = checkPartOfWord(c);
    if (!wasPartOfWord && isPartOfWord) {
      count += 1;
    }
    wasPartOfWord = isPartOfWord;
  }
  return count;
}

void test(const string& input) {
  cout << "input:\n'" << input << "'\n";
  cout << "word count: " << wordCount(input) << "\n";
}

int main(int argc, char* argv[]) {

  test("Hello, word~ I'am    li  \nNice to meet you  ");

  return 0;
}
