struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(nullptr) {}
};

//��ת�б�ѭ��
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
//��ת�б�ݹ�
ListNode * ReverseListRecursively(ListNode* head) {
	if (head == nullptr || head->next == nullptr)
		return head;

	ListNode* nxt = head->next;
	head->next = nullptr;
	ListNode* newHead = ReverseListRecursively(nxt);
	nxt->next = head;
	return newHead;
}