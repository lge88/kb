#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

struct RandomListNode {
  int label;
  RandomListNode *next, *random;
  RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

class Solution {
 public:
  RandomListNode* bfsCopy(RandomListNode* s) {
    if (s == NULL) return NULL;

    RandomListNode* res = NULL;
    queue<pair<RandomListNode*, RandomListNode**> > q;
    q.push(make_pair(s, &res));
    unordered_map<RandomListNode*, RandomListNode*> copied;
    unordered_map<RandomListNode*, RandomListNode*>::const_iterator it, end = copied.end();

    while (!q.empty()) {
      RandomListNode* from = q.front().first;
      RandomListNode** to = q.front().second;
      q.pop();

      *to = new RandomListNode(from->label);
      copied[from] = *to;

      if (from->next) {
        it = copied.find(from->next);
        if (it == end) {
          q.push(make_pair(from->next, &((*to)->next)));
        } else {
          (*to)->next = it->second;
        }
      }

      if (from->random) {
        it = copied.find(from->random);
        if (it == end) {
          q.push(make_pair(from->random, &((*to)->random)));
        } else {
          (*to)->random = it->second;
        }
      }
    }
    return res;
  }

  RandomListNode *copyRandomList(RandomListNode *head) {
    return bfsCopy(head);
  }
};

void test(RandomListNode* head) {
  Solution sol;
  cout << "from: " << head << "\n";
  cout << "to: " << sol.copyRandomList(head) << "\n";
}

int main(int argc, char* argv[]) {
  {
    RandomListNode n1(1);
    test(&n1);
  }
  return 0;
}
