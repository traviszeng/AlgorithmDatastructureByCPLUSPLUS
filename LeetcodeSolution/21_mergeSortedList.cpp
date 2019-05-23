struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(nullptr) {}
};


//合并两个排序的链表
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	if (l1 == nullptr)
		return l2;
	if (l2 == nullptr)
		return l1;
	ListNode *newHead = (l1->val <= l2->val) ? l1 : l2;
	ListNode *cur = newHead;
	if (newHead == l1)
		l1 = l1->next;
	else
		l2 = l2->next;
	while (l1 != nullptr&&l2 != nullptr) {
		if (l1->val <= l2->val)
		{
			cur->next = l1;
			l1 = l1->next;
			cur = cur->next;
		}
		else {
			cur->next = l2;
			l2 = l2->next;
			cur = cur->next;
		}
	}

	if (l1 == nullptr)
		cur->next = l2;
	if (l2 == nullptr)
		cur->next = l1;
	return newHead;
}

ListNode* mergeTwoListsRecursively(ListNode* l1, ListNode* l2) {
	if (l1 == nullptr)
		return l2;
	if (l2 == nullptr)
		return l1;
	if (l1->val <= l2->val) {
		l1->next = mergeTwoListsRecursively(l1->next, l2);
		return l1;
	}
	else {
		l2->next = mergeTwoListsRecursively(l1, l2->next);
		return l2;
	}
}