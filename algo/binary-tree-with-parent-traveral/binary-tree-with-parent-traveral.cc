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

struct TreeNode {
  TreeNode* left;
  TreeNode* right;
  TreeNode* parent;
  int val;
  TreeNode(int x): val(x), left(nullptr), right(nullptr), parent(nullptr) {};
};

void preorder(TreeNode* root, ostream& to) {
  TreeNode* cur = root;
  while (cur) {
    TreeNode* last = cur;
    while (cur) {
      to << cur->val << " ";
      last = cur;
      cur = cur->left;
    }

    if (last->right) {
      cur = last->right;
    } else {
      while (last->parent) {
        if (last->parent->right && last->parent->right != last) {
          cur = last->parent->right;
          break;
        }
        last = last->parent;
      }
    }
  }
}

void inorder(TreeNode* root, ostream& to) {
  TreeNode* cur = root;
  while (cur) {
    TreeNode* last = cur;
    while (cur) {
      last = cur;
      cur = cur->left;
    }

    cout << last->val << " ";
    if (last->right) {
      cur = last->right;
    } else {
      while (last->parent) {
        if (last->parent->right && last->parent->right != last) {
          cout << last->parent->val << " ";
          cur = last->parent->right;
          break;
        }
        last = last->parent;
      }
    }
  }
}

TreeNode* tree1() {
  auto n20 = new TreeNode(20), n8 = new TreeNode(8), n22 = new TreeNode(22);
  auto n4 = new TreeNode(4), n12 = new TreeNode(12);
  auto n5 = new TreeNode(5), n10 = new TreeNode(10), n14 = new TreeNode(14);

  n20->left = n8; n8->parent = n20;
  n20->right = n22; n22->parent = n20;

  n8->left = n4; n4->parent = n8;
  n8->right = n12; n12->parent = n8;

  n4->right = n5; n5->parent = n4;

  n12->left = n10; n10->parent = n12;
  n12->right = n14; n14->parent = n12;

  return n20;
}

void test(TreeNode* root) {
  cout << "preorder:\n";
  preorder(root, cout);
  cout << "\n";

  cout << "inorder:\n";
  inorder(root, cout);
  cout << "\n";
}

int main(int argc, char* argv[]) {

  test(tree1());

  return 0;
}
