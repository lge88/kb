#include <iostream>
#include <cstdlib>

using namespace std;

int global;

int foo(int x) {
  return x;
}

int main(int argc, char* argv[]) {
  int local = 5;
  global = 7;

  int* p1 = new int(1);
  // void* p1 = malloc(1);
  void* p2 = malloc(128);

  // TODO: print the address of function symbol
  cout << "main: " << main << "\n";
  cout << "foo: " << addressof(foo) << "\n";
  cout << "global: " << &global << "\n";
  cout << "local: " << &local << "\n";
  cout << "p1: " << p1 << "\n";
  cout << "p2: " << p2 << "\n";

  return 0;
}
