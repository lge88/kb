#include <memory>
#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// SegmentTree for range maximum query / update
class SegmentTree {
 public:
  SegmentTree(const vector<int>& A) {
    if (A.empty()) throw runtime_error("A is empty.");

    int start = 0, end = A.size() - 1;
    root.reset(build(A, start, end));
  }

  int rangeMax(int a, int b) const {
    return rangeMax(root.get(), a, b);
  }

  void update(int i, int val) {
    update(root.get(), i, val);
  }

 private:
  struct Node {
    int start, end, max;
    unique_ptr<Node> left, right;
  };

  unique_ptr<Node> root;

  Node* build(const vector<int>& A, int start, int end) {
    Node* node = new Node;
    node->start = start;
    node->end = end;

    if (start == end) {
      node->max = A[start];
      return node;
    }

    int mid = start + (end - start) / 2;
    node->left.reset(build(A, start, mid));
    node->right.reset(build(A, mid + 1, end));
    node->max = max(node->left->max, node->right->max);
    return node;
  }

  int rangeMax(Node* p, int a, int b) const {
    if (p == nullptr || p->start > b || p->end < a) return numeric_limits<int>::min();
    if (p->start >= a && p->end <= b) return p->max;

    int leftEnd = p->left->end, rightStart = p->right->start;
    if (b <= leftEnd) return rangeMax(p->left.get(), a, b);
    if (a >= rightStart) return rangeMax(p->right.get(), a, b);
    return max(rangeMax(p->left.get(), a, leftEnd), rangeMax(p->right.get(), rightStart, b));
  }

  void update(Node* p, int i, int val) {
    if (!p->left && !p->right) {
      p->max = val;
      return;
    }

    int leftEnd = p->left->end;
    if (i <= leftEnd) {
      update(p->left.get(), i, val);
    } else {
      update(p->right.get(), i, val);
    }
    p->max = max(p->left->max, p->right->max);
  }
};

void test(const SegmentTree& st, int n) {
  for (int a = -1; a < n + 1; ++a) {
    for (int b = a; b < n + 1; ++b) {
      int res = st.rangeMax(a, b);
      cout << "rangeMax(" << a << ", " << b << "): " << res << "\n";
    }
  }
}

int main(int argc, char* argv[]) {
  vector<int> A = { 1, 4, 3, 2 };
  cout << "A: [";
  for (auto x : A) cout << " " << x;
  cout << " ]\n";

  SegmentTree st(A);

  test(st, A.size());

  cout << "\nupdate(1, 0)\n";
  A[1] = 0;
  cout << "A: [";
  for (auto x : A) cout << " " << x;
  cout << " ]\n";

  st.update(1, 0);

  test(st, A.size());

  return 0;
}
