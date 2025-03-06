#include <iostream>
// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
    public:
        ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
            if (list1 == nullptr and list2 == nullptr) {
                return nullptr;
            } else if (list1 == nullptr or list2 == nullptr) {
                return list1 != nullptr ? list1 : list2;
            } else if (list1->val <= list2->val) {
                return new ListNode(list1->val, this->mergeTwoLists(list1->next, list2));
            } else if (list2->val < list1->val) {
                return new ListNode(list2->val, this->mergeTwoLists(list1, list2->next));
            } else { return nullptr; }
        }
};

int main() {
    ListNode* l1 = new ListNode(1);
    l1->next = new ListNode(2);
    l1->next->next = new ListNode(4);
    ListNode* l2 = new ListNode(1);
    l2->next = new ListNode(3);
    l2->next->next = new ListNode(4);
    Solution s;
    ListNode* mergedList = s.mergeTwoLists(l1, l2);
    // Output: 1->1->2->3->4->4
    while (mergedList != nullptr) {
        std::cout << mergedList->val << "->";
        mergedList = mergedList->next;
    }
    return 0;
}