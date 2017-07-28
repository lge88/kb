#include <algorithm>
#include <cassert>
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

template<typename C>
void printM(const C& container) {
  for (auto p : container) {
    cout << p.first << " => " << p.second << "\n";
  }
}

int main(int argc, char* argv[]) {
  map<int, int> m = {
    { 1, 2 },
    { 2, 4 },
    { 3, 6 },
  };
  printM(m);

  for (auto p : m) p.second = p.second + 1;

  cout << "\nafter modify using 'auto p : m':\n";
  printM(m);

  for (auto& p : m) p.second = p.second + 1;
  cout << "\nafter modify using 'auto& p : m':\n";
  printM(m);

  auto it = m.find(1);
  it->second *= -1;
  cout << "\nafter modify using 'auto it = m.find(1)':\n";
  printM(m);

  const auto& jt = m.find(2);
  jt->second *= -1;
  cout << "\nafter modify using 'const auto& jt = m.find(2)':\n";
  printM(m);

  return 0;
}
