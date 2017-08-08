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

class BIT {
 public:
  void reset(int n) {
    data.clear();
    data.resize(n + 1, 0);
  }

  void add(int i, int x) {
    int n = data.size() - 1;
    i += 1;
    while (i <= n) {
      data[i] += x;
      i += i & -i;
    }
  }

  int getSum(int i) {
    int sum = 0;
    i += 1;
    while (i > 0) {
      sum += data[i];
      i -= i & -i;
    }
    return sum;
  }

 private:
  vector<int> data;
};

int main(int argc, char* argv[]) {
  vector<int> A = { 0, 1, 2, 3, 4, 5 };
  int n = A.size();

  cout << "A: ";
  for (int i = 0; i < n; ++i) {
    cout << (i > 0 ? ", " : "") << A[i];
  }
  cout << "\n";

  BIT bit;
  bit.reset(n);

  for (int i = 0; i < n; ++i) bit.add(i, A[i]);

  for (int i = -1; i < n; ++i) {
    cout << "bit.getSum(" << i << "): " << bit.getSum(i) << "\n";
  }

  cout << "\nbit.add(1, 3)\n\n";
  bit.add(1, 3);

  for (int i = -1; i < n; ++i) {
    cout << "bit.getSum(" << i << "): " << bit.getSum(i) << "\n";
  }

  return 0;
}
