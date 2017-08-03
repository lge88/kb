#include <iostream>
#include <vector>

using namespace std;

void printVec(const vector<int>& A) {
  for (auto x : A) cout << x << " ";
  cout << "\n";
}

void printVec2(vector<int>& A) {
  for (auto x : A) cout << x << " ";
  cout << "\n";
}

void printVec3(vector<int>&& A) {
  for (auto x : A) cout << x << " ";
  cout << "\n";
}

int main(int argc, char* argv[]) {
  // OK
  printVec({ 1, 2, 3 });

  // Compilation errror: rvalue argument can not be used to initialize
  // lvalue reference parameter
  // printVec2({ 1, 2, 3 });

  // OK
  printVec3({ 1, 2, 3 });

  // Compilation errror: lvalue can not be bind to rvalue reference
  // parameter
  // vector<int> A = { 1, 2, 3 };
  // printVec3(A);

  return 0;
}
