#include <iostream>
#include <string>
#include <deque>
#include <cstdlib>

using namespace std;

void tail(istream& from, ostream& to, int n) {
  deque<string> buf;
  string line;
  while (getline(from, line)) {
    buf.push_back(line);
    if (buf.size() > n) buf.pop_front();
  }
  for (auto x: buf) to << x << "\n";
}

int main(int argc, char* argv[]) {
  int n = 10;
  if (argc > 1) n = atoi(argv[1]);

  tail(cin, cout, n);
  return 0;
}
