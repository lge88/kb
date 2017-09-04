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

void postorder(TreeNode* root, ostream& to) {
  TreeNode* cur = root;
  while (cur) {
    TreeNode* last = cur;
    while (cur) {
      last = cur;
      cur = cur->left;
    }

    if (last->right) {
      cur = last->right;
    } else {
      cout << last->val << " ";
      while (last->parent && last->parent->right == last) {
          last = last->parent;
          cout << last->val << " ";
      }
      if (last->parent && last->parent->right) {
        cur = last->parent->right;
      } else {
        cur = last->parent;
      }
    }
  }
}

void destroyTree(TreeNode* root) {
  TreeNode* cur = root;
  while (cur) {
    TreeNode* last = cur;
    while (cur) {
      last = cur;
      cur = cur->left;
    }

    if (last->right) {
      cur = last->right;
    } else {
      TreeNode* parent = last->parent;
      bool wasRightChild = parent && parent->right == last;
      delete last;
      while (wasRightChild) {
        last = parent;
        parent = last->parent;
        wasRightChild = parent && parent->right == last;
        delete last;
      }

      if (parent && parent->right) {
        cur = parent->right;
      } else {
        cur = parent;
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

  cout << "postorder:\n";
  postorder(root, cout);
  cout << "\n";
}

void testDestroy() {
  auto t1 = tree1();
  destroyTree(t1);
}

int main(int argc, char* argv[]) {

  // test(tree1());
  testDestroy();
  return 0;
}
