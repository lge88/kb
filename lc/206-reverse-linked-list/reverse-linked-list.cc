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

struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
 public:
  ListNode* reverseList(ListNode* head) {
    ListNode dummy(0);
    ListNode* p = head;

    while (p != NULL) {
      ListNode* next = p->next;
      ListNode* head = dummy.next;
      dummy.next = p;
      p->next = head;
      p = next;
    }

    return dummy.next;
  }
};

void printList(ListNode* head, ostream& to) {
  while (head != NULL) {
    to << head->val << " -> ";
    head = head->next;
  }
  to << "NULL";
}

void test(ListNode* head) {
  cout << "Before: ";
  printList(head, cout);
  cout << "\n";
  cout << "Reversed: ";

  Solution sol;
  ListNode* reversedHead = sol.reverseList(head);
  printList(reversedHead, cout);
  cout << "\n";
}

int main(int argc, char* argv[]) {
  {
    test(NULL);
  }

  {
    ListNode n1(1);
    test(&n1);
  }

  {
    ListNode n1(1), n2(2), n3(3);
    n1.next = &n2;
    n2.next = &n3;
    test(&n1);
  }

  return 0;
}
