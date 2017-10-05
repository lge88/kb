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

void* myMemcpy(void* dest, const void* src, size_t n) {
  char* from = (char*)src;
  char* to = (char*)dest;
  while (n-- > 0) *to++ = *from++;
  return dest;
}

void* myMemmove(void* dest, const void* src, size_t n) {
  char* from = (char*)src;
  char* to = (char*)dest;
  if (from == to || n == 0) {
    // NOOP
  }
  // Overlapped:
  // to is in [from, from + n), direct copy from left to right will erase data which is not copied yet.
  // copy from right to left solve the problem.
  else if (from < to && to < from + n) {
    from += n - 1;
    to += n - 1;
    while (n-- > 0) *to-- = *from--;
  }
  else {
    // to < from or to >= from + n, copy fron left to right
    while (n-- > 0) *to++ = *from++;
  }
  return dest;
}

void test() {
  char src[40] = "Hello world";
  char dest[40];
  fill(begin(dest), end(dest), '*');
  dest[sizeof(dest) - 1] = '\0';

  cout << "src : \"" << src << "\"\n";
  cout << "dest: \"" << dest << "\"\n";
  cout << "sizeof(src): " << sizeof(src) << "\n";
  cout << "sizeof(dest): " << sizeof(dest) << "\n";

  cout << "myMemcpy(dest, src, n)\n";
  myMemcpy(dest, src, sizeof(src));

  cout << "src : \"" << src << "\"\n";
  cout << "dest: \"" << dest << "\"\n";
  cout << "sizeof(src): " << sizeof(src) << "\n";
  cout << "sizeof(dest): " << sizeof(dest) << "\n";

  // cout << "myMemcpy(src + 3, src, n)\n";
  // myMemcpy(src + 3, src, 20);
  // int delta = 12;
  int delta = 4;
  cout << "myMemmove(src + " << delta << ", src, n)\n";
  myMemmove(src + delta, src, 20);

  cout << "src        : \"" << src << "\"\n";
  cout << "src + delta: \"" << (src + delta) << "\"\n";
  cout << "sizeof(src): " << sizeof(src) << "\n";
}

int main(int argc, char* argv[]) {

  test();

  return 0;
}
