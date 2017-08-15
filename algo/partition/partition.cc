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

// Put all elements satisfy p to the left of it, return it
// range [first, it) p => true
// range [it, end) p => false
template <typename It, typename P>
It mypartition(It first, It last, P p) {
  It l = first, r = last;
  // invarint: [first, l) satisfy p, [r, end) do not satisfy p
  while (l != r) {
    while (l != r && p(*l)) ++l;
    while (l != r && !p(*prev(r))) --r;
    if (l != r && l != prev(r)) iter_swap(l++, --r);
    // equivalent:
    // if (l < prev(r)) {
    //   --r;
    //   iter_swap(l, r);
    //   ++l;
    // }
  }
  return l;
}

template <typename It, typename P>
void test(It first, It last, P p) {
  ostream_iterator<int> oit(std::cout, " ");
  auto pivot = mypartition(first, last, p);
  copy(first, pivot, oit);
  cout << "| ";
  copy(pivot, last, oit);
  cout << "\n";
}

int main(int argc, char* argv[]) {
  ostream_iterator<int> oit(std::cout, " ");

  // seq 1 10 | sort -R | paste -s -d',' | tr -d '\n'
  vector<int> A = {4,5,6,10,7,1,3,2,9,8};
  // vector<int> A = {6,20,2,13,9,4,22,1,25,14,19,21,17,16,3,10,24,11,15,8,12,23,5,18,7};
  copy(begin(A), end(A), oit);
  cout << "\n";

  cout << "\nx > 0:\n";
  test(begin(A), end(A), [](int x) -> bool { return x > 0; });

  cout << "\nx > 10:\n";
  test(begin(A), end(A), [](int x) -> bool { return x > 10; });

  cout << "\nx <= 5:\n";
  test(begin(A), end(A), [](int x) -> bool { return x <= 5; });

  cout << "\nx < 4:\n";
  test(begin(A), end(A), [](int x) -> bool { return x < 4; });

  cout << "\nx % 2 == 0:\n";
  test(begin(A), end(A), [](int x) -> bool { return x % 2 == 0; });

  return 0;
}
