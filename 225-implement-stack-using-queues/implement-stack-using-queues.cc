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
  queue<int> q1_;
  queue<int> q2_;
  queue<int>& getActive() {
    if (q1_.empty() && !q2_.empty()) return q2_;
    return q1_;
  }
  queue<int>& getInactive() {
    if (getActive() == q1_) return q2_;
    return q1_;
  }

 public:
  // Push element x onto stack.
  void push(int x) {
    queue<int>& active = getActive();
    active.push(x);
  }

  // Removes the element on top of the stack.
  void pop() {
    queue<int>& active = getActive();
    queue<int>& inActive = getInactive();
    while (active.size() > 1) {
      inActive.push(active.front());
      active.pop();
    }
    active.pop();
  }

  // Get the top element.
  int top() {
    queue<int>& active = getActive();
    queue<int>& inActive = getInactive();
    while (active.size() > 1) {
      inActive.push(active.front());
      active.pop();
    }
    int res = active.front();
    inActive.push(res);
    active.pop();
    return res;
  }

  // Return whether the stack is empty.
  bool empty() {
    return getActive().empty();
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
