struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(nullptr) {}
};


//Á´±íµÄ²åÈëÅÅÐò
ListNode* InsertSort(ListNode* head) {
	if (head == nullptr || head->next == nullptr)
		return head;

	ListNode* newHead = head;
	ListNode* cur = head;

	cur = cur->next;
	newHead->next = nullptr;
	while (cur) {
		ListNode* temp = newHead;
		ListNode* node = cur;
		cur = cur->next;
		node->next = nullptr;
		if (node->val < temp->val) {
			node->next = newHead;
			newHead = node;
		}
		else if (temp->next == nullptr)
		{
			temp->next = node;
		}
		else {
			while (temp->next != nullptr&&temp->next->val < node->val) {
				temp = temp->next;
			}
			node->next = temp->next;
			temp->next = node;

		}
	}
	return newHead;
}
