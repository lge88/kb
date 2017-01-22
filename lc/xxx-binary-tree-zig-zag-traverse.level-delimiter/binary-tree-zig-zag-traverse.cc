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

  vector<vector<int> > levelOrderBottom(TreeNode *root) {
    vector<vector<int> > res;
    if (root == NULL) return res;

    // NULL pointer is the delimiter between levels
    queue<TreeNode*> q;
    q.push(root);
    q.push(NULL);
    vector<int> thisLevel(0);
    bool rightToLeft = false;

    while (!q.empty()) {
      TreeNode* u = q.front();
      q.pop();

      if (u != NULL) {
        thisLevel.push_back(u->val);
        if (u->left != NULL) q.push(u->left);
        if (u->right != NULL) q.push(u->right);
      } else {
        res.push_back(vector<int>(0));
        if (rightToLeft) {
          reverse(thisLevel.begin(), thisLevel.end());
        }
        swap(res.back(), thisLevel);
        rightToLeft = !rightToLeft;
        if (!q.empty()) q.push(NULL);
      }
    }

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
