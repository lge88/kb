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
#include <queue>

using namespace std;

class Stack {
  queue<int> q;

 public:
  // Push element x onto stack.
  void push(int x) {
    q.push(x);
  }

  // Removes the element on top of the stack.
  void pop() {
    int counter = q.size() - 1;
    while (counter-- > 0) {
      q.push(q.front());
      q.pop();
    }
    q.pop();
  }

  // Get the top element.
  int top() {
    int counter = q.size() - 1;
    while (counter-- > 0) {
      q.push(q.front());
      q.pop();
    }
    int res = q.front();
    q.push(res);
    q.pop();
    return res;
  }

  // Return whether the stack is empty.
  bool empty() {
    return q.empty();
  }
};

void showState(Stack& s) {
  if (s.empty()) { cout << "EMMPTY\n"; return; }
  cout << "top: " << s.top() << "\n";
}

int main(int argc, char* argv[]) {
  {
    Stack s;
    showState(s);
    s.push(1); showState(s);
    s.push(2); showState(s);
    s.push(3); showState(s);
    s.pop(); showState(s);
    s.pop(); showState(s);
    s.pop(); showState(s);
  }
  return 0;
}
