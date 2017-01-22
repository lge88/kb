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
  bool testLeaf(TreeNode* root, int x, int h) {
    int mask = 1 << (h - 1);
    TreeNode* p = root;
    while (mask >= 1) {
      if (x & mask) {
        p = p->right;
      } else {
        p = p->left;
      }
      mask >>= 1;
    }
    return p != NULL;
  }

  int findRightMost(TreeNode* root, int h) {
    int low = 0, high = (1 << h) - 1;
    int sofar = 0;
    while (low <= high) {
      int x = low + (high - low) / 2;
      if (testLeaf(root, x, h)) {
        // search right most  in [x+1, high]
        sofar = x;
        low = x + 1;
      } else {
        // right most is in [low, x-1]
        high = x - 1;
      }
    }
    return sofar;
  }

  int countNodes(TreeNode* root) {
    // 1) Find the number of levels h. O(lgN)
    // 2) User binary search find the right most leaf x, O(lg(lgN)*lgN)
    // 3) return 1<<h + x
    TreeNode* p = root;
    if (p == NULL) return 0;

    int h = 0;
    while (p->left != NULL) {
      p = p->left;
      ++h;
    }

    int x = findRightMost(root, h);
    return (1 << h) + x;
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
