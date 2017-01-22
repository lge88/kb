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
  ListNode* removeElements(ListNode* head, int val) {
    ListNode dummy(0);

    ListNode* from = head;
    ListNode* to = &dummy;

    while (from != NULL) {
      ListNode* next = from->next;
      if (from->val != val) {
        to->next = from;
        to = to->next;
        to->next = NULL;
      }
      from = next;
    }

    return dummy.next;
  }

};

void printList(ListNode* head) {
  while (head != NULL) {
    cout << head->val << " -> ";
    head = head->next;
  }
  cout << "NULL";
}

void test(ListNode* head, int val) {
  cout << "Before: ";
  printList(head);
  cout << "\n";

  cout << "Remove " << val << "\n";

  Solution sol;
  ListNode* resultListHead = sol.removeElements(head, val);
  cout << "After: ";
  printList(resultListHead);
  cout << "\n";
}

int main(int argc, char* argv[]) {

  {
    ListNode n1(1), n2(2), n3(6), n4(3), n5(4), n6(5), n7(6);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n5.next = &n6;
    n6.next = &n7;
    test(&n1, 6);
  }

  {
    ListNode* n1 = NULL;
    test(n1, 6);
  }

  {
    ListNode n1(6);
    test(&n1, 6);
  }

  {
    ListNode n1(1), n2(2), n3(6), n4(3), n5(4), n6(5), n7(6);
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n5.next = &n6;
    n6.next = &n7;
    test(&n1, 7);
  }

  return 0;
}
