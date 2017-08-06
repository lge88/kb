#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
  // vector<double> A = { 2.0, -2.0, 3.0, 5.0, -9.0, 1.0 };
  double A[] = { 2.0, -2.0, 3.0, 5.0, -9.0, 1.0 };

  cout << "min_element(A.begin(), A.end()): " << *min_element(begin(A), end(A)) << "\n";
  cout << "max_element(A.begin(), A.end()): " << *max_element(begin(A), end(A)) << "\n";

  auto res = minmax_element(begin(A), end(A));
  cout << "minmax_element(A.begin(), A.end()) min: " << *res.first
       << ", at index: " << distance(begin(A), res.first) << "\n";
  cout << "minmax_element(A.begin(), A.end()) max: " << *res.second
       << ", at index: " << distance(begin(A), res.second) << "\n";

  return 0;
}
