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

using namespace std;

class AugmentedBST {
  struct TreeNode {
    int val;
    int size;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x), left(NULL), right(NULL), size(1) {}
  };

 public:
  AugmentedBST(): root(NULL)
  {}

  ~AugmentedBST() {
    destroy(root);
  }

  void insert(int val) {
    TreeNode* newNode = new TreeNode(val);
    TreeNode** parent = &root;
    while (*parent != NULL) {
      (*parent)->size++;
      if (val > (*parent)->val) {
        parent = &((*parent)->right);
      } else {
        parent = &((*parent)->left);
      }
    }
    // *parent == NULL now
    *parent = newNode;
  }

  int kthSmallest(int k) const {
    return kthSmallestInternal(root, k);
  }

 private:
  TreeNode* root;
  void destroy(TreeNode* root) {
    if (root == NULL) return;
    destroy(root->left);
    destroy(root->right);
    delete root;
  }

  int kthSmallestInternal(TreeNode* node, int k) const {
    if (k <= 0) throw runtime_error("k < 0");
    if (node == NULL) throw runtime_error("Tree is empty");

    int nLeft = node->left == NULL ? 0 : node->left->size;
    if (k == nLeft + 1) {
      return node->val;
    } else if (k <= nLeft) {
      return kthSmallestInternal(node->left, k);
    } else {
      return kthSmallestInternal(node->right, k - nLeft - 1);
    }
  }
};

void test(const AugmentedBST& bst, int k) {
  cout << "k: " << k << " result: " << bst.kthSmallest(k) << "\n";
}

int main(int argc, char* argv[]) {
  {
    AugmentedBST bst;
    bst.insert(15);
    bst.insert(7);
    bst.insert(20);
    bst.insert(1);
    bst.insert(9);
    bst.insert(16);
    bst.insert(23);
    bst.insert(8);
    bst.insert(13);
    bst.insert(10);
    bst.insert(14);

    test(bst, 1);
    test(bst, 2);
    test(bst, 3);
    test(bst, 4);
    test(bst, 5);
    test(bst, 6);
    test(bst, 7);
    test(bst, 8);
    test(bst, 9);
    test(bst, 10);
    test(bst, 11);
  }
  return 0;
}
