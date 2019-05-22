struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(nullptr) {}
};

//翻转列表循环
ListNode* reverseListIteratively(ListNode* head) {
	if (head == nullptr)
		return nullptr;
	if (head->next == nullptr)
		return head;
	ListNode* pre = nullptr;
	ListNode* cur = head;
	ListNode* next = head->next;
	while (next) {
		cur->next = pre;
		pre = cur;
		cur = next;
		next = next->next;
	}
	cur->next = pre;
	return cur;
}
//反转列表递归
ListNode * ReverseListRecursively(ListNode* head) {
	if (head == nullptr || head->next == nullptr)
		return head;

	ListNode* nxt = head->next;
	head->next = nullptr;
	ListNode* newHead = ReverseListRecursively(nxt);
	nxt->next = head;
	return newHead;
}