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

int main(int argc, char* argv[]) {
  int A[] = { 1, 2, 4, 4, 4, 2, 3, 5 };
  int n = sizeof(A) / sizeof(int);

  cout << "A: ";
  copy(A, A + n, ostream_iterator<int>(cout, " "));
  cout << "\n";

  sort(A, A + n);
  cout << "sort: ";
  copy(A, A + n, ostream_iterator<int>(cout, " "));
  cout << "\n";

  int* p = unique(A, A + n);
  cout << "unique: ";
  copy(A, p, ostream_iterator<int>(cout, " "));
  cout << "\n";

  cout << "A: ";
  copy(A, A + n, ostream_iterator<int>(cout, " "));
  cout << "\n";
  cout << "p - A = " << (p - A) << "\n";
  cout << "*p = " << *p << "\n";

  return 0;
}
