struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(nullptr) {}
};

//�ҵ�List�����ڶ����ڵ�
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

//��תһ��
ListNode* rotateOnce(ListNode* head) {
	ListNode* temp = findListEnd(head);
	if (temp == nullptr)
		return head;
	ListNode* newHead = temp->next;
	newHead->next = head;
	temp->next = nullptr;
	return newHead;
}

//���������ж��ٸ��ڵ�
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

//��ת����
//����һ��������ת����������ÿ���ڵ������ƶ� k ��λ�ã����� k �ǷǸ���
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