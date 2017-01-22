#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int val;
  Node* left;
  Node* right;
  Node(int v): val(v), left(NULL), right(NULL) {}
};

// pre: node is not NULL
bool isLeaf(Node* node) {
  return node->left == NULL && node->right == NULL;
}

// pre: root is not NULL. Not include root and the left most leaf
void printLeftEdge(Node* root, ostream& to) {
  Node* p = root->left;
  while (p != NULL) {
    if (!isLeaf(p)) to << " " << p->val;
    p = p->left;
  }
}

// pre: root is not NULL. Not include root and the right most leaf.
void printRightEdgeReverse(Node* root, ostream& to) {
  Node* p = root->right;
  vector<int> vals;
  while (p != NULL) {
    if (!isLeaf(p)) vals.push_back(p->val);
    p = p->right;
  }
  for (int i = vals.size() - 1; i >= 0; --i) to << " " << vals[i];
}

// pre: root is not NULL.
void printLeaves(Node* root, ostream& to) {
  if (root == NULL) return;
  if (isLeaf(root)) to << " " << root->val;
  printLeaves(root->left, to);
  printLeaves(root->right, to);
}

void printBoundary(Node* root, ostream& to) {
  if (root == NULL) return;

  to << root->val;
  printLeftEdge(root, to);
  printLeaves(root, to);
  printRightEdgeReverse(root, to);
  to << "\n";
}

int main(int argc, char* argv[]) {
  {
    Node n20(20), n8(8), n22(22), n4(4), n12(12), n10(10), n14(14), n25(25);
    Node n3(3);

    n20.left = &n8;
    n20.right = &n22;
    n8.left = &n4;
    n8.right = &n12;
    n22.right = &n25;
    n12.left = &n10;
    n12.right = &n14;
    n25.right = &n3;

    printBoundary(&n20, cout);
  }
  return 0;
}
