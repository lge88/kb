#include <cassert>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <iterator>
#include <algorithm>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:

  void levelOrderTraverse(TreeNode* node, size_t levelIndex, vector<vector<int> >& res) {
    if (node) {
      if (levelIndex >= res.size()) res.resize(levelIndex + 1);
      res[levelIndex].push_back(node->val);
      levelOrderTraverse(node->left, levelIndex + 1, res);
      levelOrderTraverse(node->right, levelIndex + 1, res);
    }
  }

  void fixZigZagOrder(vector<vector<int> >& res) {
    for (size_t i = 1; i < res.size(); i += 2) {
      reverse(res[i].begin(), res[i].end());
    }
  }

  vector<vector<int> > levelOrderBottom(TreeNode *root) {
    vector<vector<int> > res;
    levelOrderTraverse(root, 0, res);
    fixZigZagOrder(res);
    return res;
  }
};

void test(TreeNode* root, const string& expected) {
  Solution sol;
  vector<vector<int> > actual = sol.levelOrderBottom(root);
  ostringstream oss;
  for (const vector<int>& row : actual) {
    for (int i = 0, len = row.size(); i < len; ++i) oss << (i > 0 ? " " : "") << row[i];
    oss << "\n";
  }
  cout << "expected:\n" << expected;
  cout << "actual:\n" << oss.str();
  cout << "\n";
  assert(oss.str() == expected);
}

int main(int argc, char* argv[]) {
  {
    TreeNode n3(3), n9(9), n20(20), n15(15), n7(7);
    n3.left = &n9; n3.right = &n20;
    n20.left = &n15; n20.right = &n7;
    string expected("3\n20 9\n15 7\n");
    test(&n3, expected);
  }
  {
    TreeNode n3(3), n9(9), n20(20), n15(15), n7(7), n6(6), n12(12);
    n3.left = &n9; n3.right = &n20;
    n20.left = &n15; n20.right = &n7;
    n15.left = &n6; n7.right = &n12;
    string expected("3\n20 9\n15 7\n12 6\n");
    test(&n3, expected);
  }
  return 0;
}
