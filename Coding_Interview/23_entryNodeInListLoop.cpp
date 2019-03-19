#include <cstdio>
#include "../../../ReviewOfCPLUSPLUS/Coding_Interview/List.h"
// ������23�������л�����ڽ��
// ��Ŀ��һ�������а�����������ҳ�������ڽ�㣿���磬��ͼ3.8�������У�
// ������ڽ���ǽ��3��

ListNode* MeetingNode(ListNode* pHead)
{
	//�ж��Ƿ���ڻ����ҵ�����һ���ڵ�
	if (pHead == nullptr)
		return nullptr;
	ListNode *pSlow = pHead;
	ListNode *pFast = pHead;

	pSlow = pSlow->m_pNext;
	if (pSlow == nullptr)
		return nullptr;
	pFast = pSlow->m_pNext;
	while (pFast != nullptr && pSlow != nullptr) {
		if (pFast == pSlow)
			return pFast;
		pSlow = pSlow->m_pNext;
		pFast = pFast->m_pNext;
		if (pFast != nullptr)
			pFast = pFast->m_pNext;
	}

	return nullptr;


}

ListNode* EntryNodeOfLoop(ListNode* pHead)
{
	//�ҵ�����һ���ڵ����Ҫ֪�����ж��ٸ��ڵ�
	//Ȼ��һ���ڵ��pHead����������n���������ڵ������ĵط���Ϊ��ڵ�
	if (pHead == nullptr)
		return nullptr;
	ListNode *pMeet = MeetingNode(pHead);
	if (pMeet == nullptr)
		return nullptr;

	int count = 1;
	ListNode *p = pMeet->m_pNext;
	while (p != pMeet) {
		p = p->m_pNext;
		count++;
	}

	delete p;
	ListNode *pFirst = pHead;
	while (count--) {
		pFirst = pFirst->m_pNext;
	}

	ListNode *pSecond = pHead;
	while (pSecond != pFirst) {
		pSecond = pSecond->m_pNext;
		pFirst = pFirst->m_pNext;
	}

	return pFirst;




}

// ==================== Test Code ====================
void Test(const char* testName, ListNode* pHead, ListNode* entryNode)
{
	if (testName != nullptr)
		printf("%s begins: ", testName);

	if (EntryNodeOfLoop(pHead) == entryNode)
		printf("Passed.\n");
	else
		printf("FAILED.\n");
}

// A list has a node, without a loop
void Test1()
{
	ListNode* pNode1 = CreateListNode(1);

	Test("Test1", pNode1, nullptr);

	DestroyList(pNode1);
}

// A list has a node, with a loop
void Test2()
{
	ListNode* pNode1 = CreateListNode(1);
	ConnectListNodes(pNode1, pNode1);

	Test("Test2", pNode1, pNode1);

	delete pNode1;
	pNode1 = nullptr;
}

// A list has multiple nodes, with a loop 
void Test3()
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
	ConnectListNodes(pNode5, pNode3);

	Test("Test3", pNode1, pNode3);

	delete pNode1;
	pNode1 = nullptr;
	delete pNode2;
	pNode2 = nullptr;
	delete pNode3;
	pNode3 = nullptr;
	delete pNode4;
	pNode4 = nullptr;
	delete pNode5;
	pNode5 = nullptr;
}

// A list has multiple nodes, with a loop 
void Test4()
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
	ConnectListNodes(pNode5, pNode1);

	Test("Test4", pNode1, pNode1);

	delete pNode1;
	pNode1 = nullptr;
	delete pNode2;
	pNode2 = nullptr;
	delete pNode3;
	pNode3 = nullptr;
	delete pNode4;
	pNode4 = nullptr;
	delete pNode5;
	pNode5 = nullptr;
}

// A list has multiple nodes, with a loop 
void Test5()
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
	ConnectListNodes(pNode5, pNode5);

	Test("Test5", pNode1, pNode5);

	delete pNode1;
	pNode1 = nullptr;
	delete pNode2;
	pNode2 = nullptr;
	delete pNode3;
	pNode3 = nullptr;
	delete pNode4;
	pNode4 = nullptr;
	delete pNode5;
	pNode5 = nullptr;
}

// A list has multiple nodes, without a loop 
void Test6()
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

	Test("Test6", pNode1, nullptr);

	DestroyList(pNode1);
}

// Empty list
void Test7()
{
	Test("Test7", nullptr, nullptr);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();

	return 0;
}