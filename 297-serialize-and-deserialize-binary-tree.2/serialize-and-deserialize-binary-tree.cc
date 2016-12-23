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
#include <cstdlib>

using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    if (root == NULL) return "#,";
    ostringstream oss;
    oss << root->val << ",";
    oss << serialize(root->left) << serialize(root->right);
    return oss.str();
  }

  // Success: return true, i stops at one pass separator ',', num is
  // set to parsed number.
  // Fail: return false
  bool parseNumber(const string& data, int& i, int& num) {
    int n = data.size();
    int start = i, end = i;
    while (end < n && data[end] != ',') {
      if (data[end] < '0' || data[end] > '9') return false;
      ++end;
    }
    // end == n || data[end] == ','

    // Missing separator
    if (end == n) return false;

    // data[end] == ','
    num = atoi(data.substr(start, end - start).c_str());
    i = end + 1;
    return true;
  }

  // Success: return true, i stops at one pass separator ','.
  // Fail: return false, i is not changed.
  bool parseNull(const string& data, int& i) {
    int n = data.size();
    if (i + 1 >= n) return false;
    if (data[i] == '#' && data[i + 1] == ',') {
      i += 2;
      return true;
    }
    return false;
  }

  TreeNode* deserializeHelper(string data, int& i) {
    int n = data.size();

    if (i >= n) throw runtime_error("Incomplete binary tree!");

    if (parseNull(data, i)) {
      return NULL;
    }

    int num;
    if (parseNumber(data, i, num)) {
      TreeNode* node = new TreeNode(num);
      node->left = deserializeHelper(data, i);
      node->right = deserializeHelper(data, i);
      return node;
    }

    ostringstream oss;
    oss << "Unrecognized token starts at " << i << ": " << data[i];
    throw runtime_error(oss.str());
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    int i = 0;
    TreeNode* root = deserializeHelper(data, i);
    if (i != data.size()) throw runtime_error("Input has redundant data!");
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
  // test("x,");
  // test("69");
  test("6,#,#,");
  // test("6,#,#");
  test("6,2,1,#,#,4,3,#,#,5,#,#,8,#,9,#,#,");
  // test("6,2,1,#,#,4,3,#,#,5,#,#,8,#,9,");
  test("6,2,1,#,#,4,3,#,#,5,#,#,8,#,9,#,#,7,#,#,");

  return 0;
}
