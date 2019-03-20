#include<iostream>
#include <cstdio>

#include "List.h"


ListNode* ReverseList(ListNode* pHead) {
	if (pHead == nullptr)
		return nullptr;
	if (pHead->m_pNext == nullptr)
		return pHead;
	ListNode *pBefore  = nullptr;
	ListNode *pAfter = nullptr;
	ListNode *pNow = pHead;

	while (pNow != nullptr) {
		pAfter = pNow->m_pNext;
		pNow->m_pNext = pBefore;
		pBefore = pNow;
		pNow = pAfter;
	}

	return pBefore;


}



// ====================���Դ���====================
ListNode* Test(ListNode* pHead)
{
	printf("The original list is: \n");
	PrintList(pHead);

	ListNode* pReversedHead = ReverseList(pHead);

	printf("The reversed list is: \n");
	PrintList(pReversedHead);

	return pReversedHead;
}
// ����������ж�����
void Test1()
{
	ListNode* pNode1 = CreateListNode(1);
	ListNode* pNode2 = CreateListNode(2);
	ListNode* pNode3 = CreateListNode(3);
	ListNode* pNode4 = CreateListNode(4);
	ListNode* pNode5 = CreateListNode(5);

	ConnectListNodes(pNode1, pNode2);
	ConnectListNodes(pNode2, pNode3);
	ConnectListNodes(pNode3, pNode4);
	ConnectListNodes(pNode4, pNode5);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// ���������ֻ��һ�����
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);

	ListNode* pReversedHead = Test(pNode1);

	DestroyList(pReversedHead);
}

// ���������
void Test3()
{
	Test(nullptr);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	system("pause");

	return 0;
}