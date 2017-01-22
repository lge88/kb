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

int gcd(int a, int b) {
  assert(a != 0 && b != 0);
  a = a > 0 ? a : -a;
  b = b > 0 ? b : -b;
  while (b %= a) swap(a, b);
  return a;
}

int main(int argc, char* argv[]) {
  assert(argc >= 3);
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);
  cout << gcd(a, b) << "\n";
  return 0;
}
