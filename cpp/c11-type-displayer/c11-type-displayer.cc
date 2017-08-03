#include <iostream>
#include <unordered_map>

using namespace std;

template <typename T> class TD;

template<typename T>
void f(T param) {
  TD<decltype(param)> x;
}

template<typename T>
void g(T& param) {
  TD<decltype(param)> x;
  // cout << param[6] << "\n";
}

template<typename T>
void h(T&& param) {
  TD<decltype(param)> x;
}

int sum(int a, int b) { return a + b; }

int main(int argc, char* argv[]) {
  // 1) Show deduced auto type

  // unordered_map<int, int> m = {
  //   { 1, 2 },
  //   { 2, 4 },
  //   { 3, 6 },
  // };
  // auto it = m.find(1);
  // TD<decltype(it)> x;

  // 2) Show deduced type for f, notice deduced type lost const in
  // value itself, but pointer constness is preserved.

  // const char* const ptr = "Fun with pointers";
  // TD<decltype(ptr)> x;
  // f(ptr);

  // 3) Show deduced type for array arguments, array decays to pointer
  // when ParamType is T. When ParamType is T&, the type deduced does
  // distingush pointer and array reference.

  // int a[] = { 1, 2, 3, 4, 5 };
  // TD<decltype(a)> x;
  // f(a);
  // g(a);

  // 4) Show deduced type for template function h, where ParamType is
  // T&&, a universal reference. When argument is a lvalue, deduced
  // type is lvalue reference. Otherwise, which is the normal case,
  // deduced type is rvalue reference.

  // h(13);
  // h(sum(1, 2));
  int x = 10;
  h(x);

  return 0;
}
