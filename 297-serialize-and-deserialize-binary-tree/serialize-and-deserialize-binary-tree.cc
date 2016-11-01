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
};

class Codec {
 public:
  void serializeHelper(TreeNode* root, ostringstream& oss) {
    if (root == NULL) {
      oss << "#,";
    } else {
      oss << root->val << ',';
      serializeHelper(root->left, oss);
      serializeHelper(root->right, oss);
    }
  }

  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    ostringstream oss;
    serializeHelper(root, oss);
    return oss.str();
  }

  void deserializeHelper(TreeNode** root, const string& data, int& i) {
    int n = data.size();
    // cout << "n: " << n << ", i: " << i << endl;
    if (i >= n) return;

    int j = i + 1;
    while (j < n && data[j] != ',') ++j;

    const string token(data.substr(i, j - i));
    i = j + 1;

    if (token != "#") {
      // read int val
      int val = atoi(token.c_str());
      *root = new TreeNode(val);
      deserializeHelper(&(*root)->left, data, i);
      deserializeHelper(&(*root)->right, data, i);
    }
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    int i = 0;
    TreeNode* root = NULL;
    deserializeHelper(&root, data, i);
    return root;
  }
};

void test(const string& s) {
  Codec codec;
  cout << "s: " << s << "\n";
  cout << "serialize(deserialize(s)): " << codec.serialize(codec.deserialize(s)) << "\n\n";
}

int main(int argc, char* argv[]) {

  test("#,");
  test("6,#,#,");
  test("6,2,1,#,#,4,3,#,#,5,#,#,8,#,9,#,#,");

  return 0;
}
