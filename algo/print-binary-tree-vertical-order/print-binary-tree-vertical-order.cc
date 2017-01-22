#include <iostream>
#include <iomanip>
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

struct Node {
  int val;
  Node* left;
  Node* right;
  Node(int v): val(v), left(NULL), right(NULL) {}
};

void dfs(Node* root, int curX, map<int, vector<int> >& valByX) {
  if (root == NULL) return;
  valByX[curX].push_back(root->val);
  dfs(root->left, curX - 1, valByX);
  dfs(root->right, curX + 1, valByX);
}

void printTreeVerticalOrder(Node* root, ostream& to) {
  map<int, vector<int> > valByX;
  dfs(root, 0, valByX);
  for (map<int, vector<int> >::const_iterator it = valByX.begin();
       it != valByX.end(); ++it) {
    to << setw(5) << it->first << ": ";
    const vector<int>& vals(it->second);
    for (size_t i = 0; i < vals.size(); ++i) to << (i > 0 ? " " : "") << vals[i];
    to << "\n";
  }
}

int main(int argc, char* argv[]) {
  {
    Node n1(1), n2(2), n3(3), n4(4), n5(5);

    n1.left = &n2;
    n1.right = &n3;
    n2.left = &n4;
    n3.left = &n5;

    printTreeVerticalOrder(&n1, cout);
  }
  return 0;
}
