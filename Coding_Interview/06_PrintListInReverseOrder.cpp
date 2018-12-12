/**
����ڵ㶨��
*/
#include<stack>
#include<iostream>

using namespace std;
struct ListNode{
	int mValue;
	ListNode *next;
};


//���һ���½ڵ㵽����β��
//params: 
//phead ָ��ͷ����ָ��
//value �½ڵ��value
void addToTail(ListNode **phead, int value) {
	ListNode *newNode = new ListNode();
	newNode->mValue = value;
	newNode->next = nullptr;

	if (*phead == nullptr) {
		//����Ϊ��
		*phead = newNode;
	}
	else {
		//����Ϊ��
		ListNode *currentNode = *phead;
		while (currentNode->next != nullptr)
			currentNode = currentNode->next;
		currentNode->next = newNode;
	}
}

//�Ƴ�ֵΪvalue����Ӧ�ڵ�
//params: 
//phead ָ��ͷ����ָ��
//value Ѱ�ҵĽڵ��value
void removeNode(ListNode **phead, int value) {
	if (*phead == nullptr || phead ==nullptr)
		return;
	ListNode *currentNode = (*phead)->next;
	ListNode *previousNode = *phead;
	if (previousNode->mValue == value){
		delete *phead;
		*phead = currentNode;
		return;
	}

	while (currentNode != nullptr && currentNode->mValue != value) {
		currentNode = currentNode->next;
		previousNode = previousNode->next;
	}
	if (currentNode->mValue == value && currentNode->next == nullptr) {
		previousNode->next = nullptr;
		delete currentNode;
		return;
	}
	else if (currentNode->mValue == value &&currentNode->next != nullptr) {
		previousNode->next = currentNode->next;
		delete currentNode;
		return;
	}
	else
		return;
}

// ������6����β��ͷ��ӡ����
// ��Ŀ������һ�������ͷ��㣬��β��ͷ��������ӡ��ÿ������ֵ��
void printListReversingly_Interatively(ListNode *pHead) {
	std::stack<ListNode*> nodes;

	ListNode *currentNode = pHead;
	while (currentNode != nullptr) {
		nodes.push(currentNode);
		currentNode = currentNode->next;
	}

	while (!nodes.empty()) {
		currentNode = nodes.top();
		cout << "current value is:" << currentNode->mValue << endl;
		nodes.pop();
	}
}
//�ݹ� ÿ�α���ʱ�ȵݹ�������ڵ��ֵ
void PrintListReversingly_Recursively(ListNode* pHead)
{
	if (pHead != nullptr)
	{
		if (pHead->next != nullptr)
		{
			PrintListReversingly_Recursively(pHead->next);
		}

		printf("%d\t", pHead->mValue);
	}
}

