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
#include <stack>

using namespace std;

class Queue {
  stack<int> s1, s2;

 public:
  // Push element x to the back of queue.
  void push(int x) {
    while (!s2.empty()) {
      s1.push(s2.top());
      s2.pop();
    }
    s1.push(x);
    while (!s1.empty()) {
      s2.push(s1.top());
      s1.pop();
    }
  }

  // Removes the element from in front of queue.
  void pop(void) {
    s2.pop();
  }

  // Get the front element.
  int peek(void) {
    return s2.top();
  }

  // Return whether the queue is empty.
  bool empty(void) {
    return s2.empty();
  }
};

void showState(Queue& q) {
  if (q.empty()) { cout << "EMMPTY\n"; return; }
  cout << "peek: " << q.peek() << "\n";
}

int main(int argc, char* argv[]) {
  {
    Queue q;
    showState(q);
    q.push(1); showState(q);
    q.push(2); showState(q);
    q.push(3); showState(q);
    q.pop(); showState(q);
    q.pop(); showState(q);
    q.pop(); showState(q);
  }
  return 0;
}
