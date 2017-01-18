#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include <cassert>

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

    queue<TreeNode*> q;
    q.push(root);

    res.push_back(vector<int>(1, root->val));
    bool rightToLeft = true;
    int thisLevelRemains = 1;
    vector<int> nextLevel;

    while (!q.empty()) {
      TreeNode* node = q.front();
      q.pop();

      if (node->left != NULL) {
        q.push(node->left);
        nextLevel.push_back(node->left->val);
      }

      if (node->right != NULL) {
        q.push(node->right);
        nextLevel.push_back(node->right->val);
      }

      --thisLevelRemains;
      if (thisLevelRemains == 0) {
        if (rightToLeft) {
          reverse(nextLevel.begin(), nextLevel.end());
        }

        thisLevelRemains = nextLevel.size();
        rightToLeft = !rightToLeft;
        if (nextLevel.size() > 0) {
          res.push_back(vector<int>(0));
          swap(res.back(), nextLevel);
        }
      }
    }

    return res;
  }
};

void test(TreeNode* root) {
  Solution sol;
  vector<vector<int> > actual = sol.levelOrderBottom(root);
  cout << "[\n";
  for (const vector<int>& row : actual) {
    cout << "  [";
    for (int el : row) cout << " " << el;
    cout << " ]\n";
  }
  cout << "]\n\n";
}

int main(int argc, char* argv[]) {
  {
    TreeNode n3(3), n9(9), n20(20), n15(15), n7(7);
    n3.left = &n9; n3.right = &n20;
    n20.left = &n15; n20.right = &n7;
    test(&n3);
  }
  {
    TreeNode n3(3), n9(9), n20(20), n15(15), n7(7), n6(6), n12(12);
    n3.left = &n9; n3.right = &n20;
    n20.left = &n15; n20.right = &n7;
    n15.left = &n6;
    n7.right = &n12;
    test(&n3);
  }
  return 0;
}
