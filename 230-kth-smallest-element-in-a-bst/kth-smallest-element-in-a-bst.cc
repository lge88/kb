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
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x): val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:
  void buildSortedArray(TreeNode* n, vector<int>& A) {
    if (n == NULL) return;
    buildSortedArray(n->left, A);
    A.push_back(n->val);
    buildSortedArray(n->right, A);
  }

  int kthSmallest(TreeNode* root, int k) {
    vector<int> A;
    buildSortedArray(root, A);
    return A[k - 1];
  }
};

void test(TreeNode* root, int k) {
  Solution sol;
  cout << "k: " << k << " result: " << sol.kthSmallest(root, k) << "\n";
}

int main(int argc, char* argv[]) {
  {
    TreeNode n15(15), n7(7), n20(20), n1(1), n9(9), n16(16), n23(23);
    TreeNode n8(8), n13(13), n10(10), n14(14);

    n15.left = &n7;
    n15.right = &n20;
    n7.left = &n1;
    n7.right = &n9;
    n20.left = &n16;
    n20.right = &n23;
    n9.left = &n8;
    n9.right = &n13;
    n13.left = &n10;
    n13.right = &n14;

    test(&n15, 1);
    test(&n15, 2);
    test(&n15, 3);
    test(&n15, 4);
    test(&n15, 5);
    test(&n15, 6);
    test(&n15, 7);
    test(&n15, 8);
    test(&n15, 9);
    test(&n15, 10);
    test(&n15, 11);
  }
  return 0;
}
