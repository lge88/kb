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

// dir = 0 => UP, dir = 1 => LEFT,
// dir = 2 => DOWN, dir = 3 => RIGHT
struct State {
  int x, y, dir;
};

State simulate(string command, State s = { 0, 0, 0 }) {
  static const int dx[4] = { 0, -1, 0, 1 };
  static const int dy[4] = { 1, 0, -1, 0 };

  // State s = { 0, 0, 0 };
  for (auto cmd : command) {
    if (cmd == 'L') {
      s.dir = (s.dir + 1) % 4;
    } else if (cmd == 'R') {
      s.dir = s.dir - 1;
      if (s.dir < 0) s.dir = 3;
    } else if (cmd == 'G') {
      s.x += dx[s.dir];
      s.y += dy[s.dir];
    }
  }
  return s;
}

bool doesCircleExist(string command) {
  State s = simulate(command);

  // cout << "state: " << s.x << ", " << s.y << ", " << s.dir << "\n";
  if (s.dir == 0) return s.x == 0 && s.y == 0;
  // if (s.dir == 2) return true;
  return true;
}

vector < string > doesCircleExist(vector < string > commands) {
  auto res = vector<string>();
  for (auto command : commands) {
    // cout << "0: 0, 0, 0\n";
    // State s = { 0, 0, 0 };
    // for (int i = 0; i < 6; i++) {
    //   s = simulate(command, s);
    //   cout << i << ": " << s.x << ", " << s.y << ", " << s.dir << "\n";
    // }

    if (doesCircleExist(command)) {
      res.push_back("YES");
    } else {
      res.push_back("NO");
    }
  }
  return res;
}

int main() {
  vector < string > res;

  int _commands_size = 0;
  cin >> _commands_size;
  cin.ignore (std::numeric_limits<std::streamsize>::max(), '\n');
  vector<string> _commands;
  string _commands_item;
  for(int _commands_i=0; _commands_i<_commands_size; _commands_i++) {
    getline(cin, _commands_item);
    _commands.push_back(_commands_item);
  }

  res = doesCircleExist(_commands);
  for(int res_i=0; res_i < res.size(); res_i++) {
    cout << res[res_i] << endl;;
  }

  return 0;
}
