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

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
  TreeNode() : val(0), left(NULL), right(NULL) {}
};

class Solution {
 public:
  int countNodes(TreeNode* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
  }
};

void test(TreeNode* root) {
  Solution sol;
  cout << "node cout: " << sol.countNodes(root) << "\n";
}

int main(int argc, char* argv[]) {
  {
    TreeNode n1, n2, n3, n4, n5;
    TreeNode n6, n7, n8, n9, n10;
    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n2.right = &n5;
    n3.left = &n6;
    n3.right = &n7;
    n4.left = &n8;
    n4.right = &n9;
    n5.left = &n10;
    test(&n1);
  }
  return 0;
}
