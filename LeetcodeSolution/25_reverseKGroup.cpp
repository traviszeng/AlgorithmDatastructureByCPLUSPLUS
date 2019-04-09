#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(nullptr) {}
};

ListNode* reverseKGroup(ListNode* head, int k) {
	if (head == nullptr || head->next == nullptr)
		return head;
	ListNode *pHead = head;
	ListNode *pNewHead = head;
	ListNode *pCur = new ListNode(-1);
	int n = 0;
	while (1) {
		ListNode *pStart = pHead;
		ListNode *pEnd = pHead;
		if (pStart == nullptr || pStart->next == nullptr) break;
		ListNode *pNext = pStart->next;

		int kk = k;
		while (kk--)
		{
			if (pEnd != nullptr)
				pEnd = pEnd->next;
			else {
				pEnd = pStart;
				break;
			}
		}
		if (pEnd == pStart)
			break;
		kk = k;
		while (--kk) {
			pNext = pStart->next;
			pStart->next = pNext->next;
			pNext->next = pHead;
			pHead = pNext;

		}
		if (n == 0) {
			pNewHead = pHead;
			//pCur->next = pNewHead;
		}
		pCur->next = pHead;
		for (int i = 0; i < k; i++)
			pCur = pCur->next;

		n++;
		pHead = pEnd;
	}
	return pNewHead;

}

ListNode * createList(vector<int>  a) {
	ListNode* head;
	ListNode *tmp = new ListNode(a[0]);
	head = tmp;
	ListNode *cur = tmp;
	for (int i = 1; i < a.size(); i++) {
		ListNode *t = new ListNode(a[i]);
		cur->next = t;
		cur = t;
	}
	return head;
}


int main() {
	vector<int> a{ 1,2,3,4,5 };
	ListNode * head = createList(a);
	reverseKGroup(head, 2);

}