/**
链表节点定义
*/
#include<stack>
#include<iostream>

using namespace std;
struct ListNode{
	int mValue;
	ListNode *next;
};


//添加一个新节点到链表尾端
//params: 
//phead 指向头结点的指针
//value 新节点的value
void addToTail(ListNode **phead, int value) {
	ListNode *newNode = new ListNode();
	newNode->mValue = value;
	newNode->next = nullptr;

	if (*phead == nullptr) {
		//链表为空
		*phead = newNode;
	}
	else {
		//链表不为空
		ListNode *currentNode = *phead;
		while (currentNode->next != nullptr)
			currentNode = currentNode->next;
		currentNode->next = newNode;
	}
}

//移除值为value的相应节点
//params: 
//phead 指向头结点的指针
//value 寻找的节点的value
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

// 面试题6：从尾到头打印链表
// 题目：输入一个链表的头结点，从尾到头反过来打印出每个结点的值。
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
//递归 每次遍历时先递归输出其后节点的值
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

