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

int myMemcmp(const void* lhs, const void* rhs, size_t n) {
  auto p1 = (unsigned char*) lhs;
  auto p2 = (unsigned char*) rhs;
  for (; n-- > 0; p1++, p2++) {
    if (*p1 != *p2) {
      return *p1 - *p2;
    }
  }
  return 0;
}

void test(const void* lhs, const void* rhs, size_t n) {
  cout << "lhs: \"" << (const char*) lhs << "\"\n";
  cout << "rhs: \"" << (const char*) rhs << "\"\n";
  cout << "myMemcmp(lhs, rhs, " << n << "): " << myMemcmp(lhs, rhs, n) << "\n\n";
}

int main(int argc, char* argv[]) {

  const char s1[] = "abcd";
  const char s2[] = "abcd";
  const char s3[] = "abcf";
  const char s4[] = "abca";
  test(s1, s2, 4);
  test(s1, s3, 4);
  test(s1, s4, 4);

  return 0;
}
