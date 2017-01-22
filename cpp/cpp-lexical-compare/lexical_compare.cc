#include <iostream>
#include <vector>

using namespace std;

#define EVAL(exp) cout << #exp <<  " => " << (exp) << "\n"

int main(int argc, char* argv[]) {

  vector<int> v1 = {};
  vector<int> v2 = { 1 };
  vector<int> v3 = { 1, 2 };
  vector<int> v4 = { 1, 3 };
  vector<int> v5 = { 2, 1 };

  EVAL(v1 < v2);
  EVAL(v2 < v3);
  EVAL(v3 < v4);
  EVAL(v4 < v5);

  return 0;
}
