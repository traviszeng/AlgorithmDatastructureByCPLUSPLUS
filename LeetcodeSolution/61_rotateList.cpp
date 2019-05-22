struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(nullptr) {}
};

//找到List倒数第二个节点
ListNode* findListEnd(ListNode* head) {
	if (head == nullptr)
		return  nullptr;
	if (head->next == nullptr)
		return nullptr;
	if (head->next->next == nullptr)
		return head;
	ListNode* temp = head;
	while (temp->next->next) {
		temp = temp->next;
	}
	return temp;
}

//旋转一步
ListNode* rotateOnce(ListNode* head) {
	ListNode* temp = findListEnd(head);
	if (temp == nullptr)
		return head;
	ListNode* newHead = temp->next;
	newHead->next = head;
	temp->next = nullptr;
	return newHead;
}

//计算链表有多少个节点
int countNode(ListNode* head) {
	if (head == nullptr)
		return 0;
	ListNode* temp = head;
	int num = 0;
	while (temp) {
		num += 1;
		temp = temp->next;
	}
	return num;
}

//旋转链表
//给定一个链表，旋转链表，将链表每个节点向右移动 k 个位置，其中 k 是非负数
ListNode* rotateRight(ListNode* head, int k) {
	if (head == nullptr)
		return nullptr;
	int nodeNum = countNode(head);
	if (nodeNum == 1)
		return head;
	if (k > nodeNum)
		return rotateRight(head, k%nodeNum);

	for (int i = 0; i < k; i++) {
		head = rotateOnce(head);
	}
	return head;
}