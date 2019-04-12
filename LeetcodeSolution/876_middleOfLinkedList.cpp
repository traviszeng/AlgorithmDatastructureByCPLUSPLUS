#include<iostream>
using namespace std;

/**
 * Definition for singly-linked list.
 */

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
	
};

ListNode* middleNode(ListNode* head) {
	if (head == nullptr)
		return nullptr;

	if (head->next == nullptr)
		return head;
	if (head->next->next == nullptr)
		return head->next;
	ListNode *cur = head;
	int num = 0;
	while (cur != nullptr) {
		cur = cur->next;
		num++;
	}
	//cout<<num;
	//return head;

	cur = head;
	num = num / 2;
	while (num != 0) {
		cur = cur->next;
		num--;
	}
	return cur;
}