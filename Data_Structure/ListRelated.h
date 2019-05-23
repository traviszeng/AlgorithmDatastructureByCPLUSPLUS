#pragma once
#include<iostream>

/**
���������㷨����
*/

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x) ,next(nullptr){}
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


//��ת�б����
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


//�ϲ�����������������
ListNode* mergeTwoListsIteratively(ListNode* l1, ListNode* l2) {
	if (l1 == nullptr)
		return l2;
	if (l2 == nullptr)
		return l1;
	ListNode *newHead = (l1->val<=l2->val)?l1:l2;
	ListNode *cur  = newHead;
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

//��������ĳ��ȼ�β�ڵ�ָ��
int GetListLength(ListNode* head, ListNode*& back) {
	if (head == nullptr)
		return 0;
	int length = 1;
	back = head;
	while (back->next != nullptr) {
		back = back->next;
		length++;
	}
	return length;
}


//��������ĵ�һ�������ڵ�
ListNode* FindFirstCommonNode(ListNode *pHead1, ListNode *pHead2) {
	ListNode *back1 = nullptr;
	int l1 = GetListLength(pHead1, back1);  
	ListNode *back2 = nullptr;
	int l2 = GetListLength(pHead2, back2);

	if (back1 != back2)   // û�й����ڵ�
		return nullptr;

	ListNode *p1 = pHead1;
	ListNode *p2 = pHead2;
	if (l1 > l2) {
		int d = l1 - l2;
		while (d--)
			p1 = p1->next;
		while (p1 != p2) {
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	else {
		int d = l2 - l1;
		while (d--)
			p2 = p2->next;
		while (p1 != p2) {
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	return p1;
}

void swap(ListNode* &a, ListNode* &b) {
	int temp = a->val;
	a->val = b->val;
	b->val = temp;
}


ListNode* partition(ListNode* low, ListNode* high) {
	auto mid = low;
	int key = low->val;
	for (auto i = low->next; i != high; i = i->next) {
		if (i->val < key) {
			mid = mid->next;
			swap(mid, i);
		}
	}
	swap(low, mid);
	return mid;
}

//�����������
void quickSortList(ListNode* low, ListNode* high) {
	if (low == high || low->next == high)
		return;
	auto mid = partition(low, high);
	quickSortList(low, mid);
	quickSortList(mid->next, high);
	
}


//�����������
ListNode* QuickSort(ListNode* head) {
	if (head == nullptr || head->next == nullptr)
		return head;

	quickSortList(head, nullptr);
	return head;
}


ListNode* merge(ListNode* head, ListNode* head2) {
	if (head == nullptr)
		return head2;
	if (head2 == nullptr)
		return head;
	ListNode* newHead;
	if (head->val < head2->val)
	{
		newHead = head;
		head = head->next;

	}
	else {
		newHead = head2;
		head2 = head2->next;
	}

	ListNode* cur = newHead;
	while (head&&head2) {
		if (head->val < head2->val) {
			cur->next = head;
			head = head->next;
			cur = cur->next;
		}
		else {
			cur->next = head2;
			head2 = head2->next;
			cur = cur->next;

		}
	}
	if (head != nullptr)
		cur->next = head;
	if (head2 != nullptr)
		cur->next = head2;
	return newHead;
}


//����Ĺ鲢����
ListNode* MergeSort(ListNode* head) {
	if (head == nullptr || head->next == nullptr)
		return head;
	ListNode* fast = head;
	ListNode* slow = head;
	while (fast->next&&fast->next->next) {
		fast = fast->next->next;
		slow = slow->next;

	}

	auto mid = slow->next;
	slow->next = nullptr;

	head = MergeSort(head);
	mid = MergeSort(mid);

	return merge(head, mid);
}


//��ӡ����
void printListNode(ListNode* head) {
	if (head == nullptr)
		std::cout << "Empty list!\n";
	ListNode* temp=head;
	while (temp->next) {
		std::cout << temp->val << "->";
		temp = temp->next;
	}
	std::cout << temp->val << "\n";
}

//��������
ListNode* InsertSort(ListNode* head) {
	if (head == nullptr||head->next==nullptr)
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

//ѡ������
ListNode* SelectionSort(ListNode* head) {
	if (head == nullptr || head->next == nullptr)
		return head;

	ListNode* newHead = nullptr;
	ListNode* fast = head->next;
	ListNode* slow = head;
	ListNode* min = head;
	ListNode* minpre = head;
	while (fast) {
		if (fast->val < min->val) {
			min = fast;
			minpre = slow;
		}
		fast = fast->next;
		slow = slow->next;
	}

	if (head == min)
	{
		newHead = head;
		head = head->next;
		newHead->next = nullptr;
	}
	else {
		newHead = min;
		minpre->next = min->next;
		min->next = nullptr;
	}

	ListNode *newCur = newHead;
	while (head != nullptr) {
		fast = head->next;
		slow = head;
		if (slow == nullptr)
			break;
		min = head;
		minpre = head;
		while (fast) {
			if (fast->val < min->val) {
				min = fast;
				minpre = slow;
			}
			fast = fast->next;
			slow = slow->next;
		}

		if (head == min)
		{
			newCur->next = head;
			head = head->next;
			
		}
		else {
			newCur->next = min;
			minpre->next = min->next;
			min->next = nullptr;
		}
		newCur = newCur->next;
	}
	return newHead;

}

//ð������
ListNode* BubbleSort(ListNode* head) {
	if (head == nullptr || head->next == nullptr)
		return head;

	ListNode* maxLoc = nullptr;
	for (auto cur = head; cur->next != nullptr; cur = cur->next) {
		ListNode *max = maxLoc;
		for (auto i = head; i->next != max; i = i->next) {
			if (i->val > i->next->val) {
				swap(i, i->next);
				maxLoc = i->next;
			}
		}
		printListNode(head);
	}
	return head;
}
