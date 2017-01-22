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

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

ostream& operator<<(ostream& to, const TreeNode* root) {
  if (root == NULL) return to;

  queue<const TreeNode*> q;
  q.push(root);
  int thisLevelRemaining = 1;
  int nextLevelRemaining = 0;

  while (!q.empty()) {
    const TreeNode* n = q.front();
    q.pop();

    to << n->val << " ";

    if (n->left != NULL) {
      q.push(n->left);
      ++nextLevelRemaining;
    }

    if (n->right != NULL) {
      q.push(n->right);
      ++nextLevelRemaining;
    }

    thisLevelRemaining--;
    if (thisLevelRemaining == 0) {
      to << "\n";
      thisLevelRemaining = nextLevelRemaining;
      nextLevelRemaining = 0;
    }
  }

  return to;
}


class Solution {
 public:
  TreeNode* invertTree(TreeNode* root) {
    if (root == NULL) return NULL;
    TreeNode* l = invertTree(root->left);
    TreeNode* r = invertTree(root->right);
    root->right = l;
    root->left = r;
    return root;
  }
};

void test(TreeNode* x) {
  Solution sol;
  cout << "x:\n" << x << "\n";
  cout << "inverted:\n" << sol.invertTree(x) << "\n\n";
}

int main(int argc, char* argv[]) {
  {
    TreeNode n1(1), n2(2), n3(3), n4(4), n6(6), n7(7), n9(9);
    n4.left = &n2;
    n4.right = &n7;
    n2.left = &n1;
    n2.right = &n3;
    n7.left = &n6;
    n7.right = &n9;
    test(&n4);
  }
  return 0;
}
