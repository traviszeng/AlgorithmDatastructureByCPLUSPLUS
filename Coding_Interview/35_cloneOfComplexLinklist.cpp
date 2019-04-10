#include <cstdio>
#include<iostream>
#include "ComplexList.h"


using namespace std;


//��¡�ڵ� �����ƵĽڵ�����ԭ�нڵ�֮��
void CloneNodes(ComplexListNode *head) {
	if (head == nullptr)
		return;
	ComplexListNode *cur = head;
	while (cur != nullptr) {
		ComplexListNode *pClone = new ComplexListNode();
		pClone->m_pNext = cur->m_pNext;
		pClone->m_nValue = cur->m_nValue;
		cur->m_pNext = pClone;
		pClone->m_pSibling = nullptr;
		cur = pClone->m_pNext;
	}
}

//����¡�ڵ����ԭ���ڵ��������Ϣ���ӵ���Ӧ�Ŀ�¡�ڵ�
void ConnectSiblingNodes(ComplexListNode *head) {
	ComplexListNode *cur = head;
	while (cur != nullptr&&cur->m_pNext!=nullptr) {
		if (cur->m_nValue == cur->m_pNext->m_nValue) {
			cur->m_pNext->m_pSibling = cur->m_pSibling;
			
		}
		cur = cur->m_pNext;
	}
}

ComplexListNode * ReconnectNodes(ComplexListNode *head) {
	ComplexListNode *newHead = nullptr;
	ComplexListNode *newCur = nullptr;
	ComplexListNode *cur = head;
	while (cur != nullptr) {
		if (cur->m_nValue == cur->m_pNext->m_nValue) {
			if (newHead == nullptr) {
				newHead = cur->m_pNext;
				newCur = cur->m_pNext;
			}
			else {
				newCur->m_pNext = cur->m_pNext;
				newCur = newCur->m_pNext;
			}

			cur->m_pNext = cur->m_pNext->m_pNext;
		}
		cur = cur->m_pNext;
	}
	return newHead;
}


ComplexListNode *Clone(ComplexListNode *head) {
	CloneNodes(head);
	ConnectSiblingNodes(head);
	return ReconnectNodes(head);
}


// ====================���Դ���====================
void Test(const char* testName, ComplexListNode* pHead)
{
	if (testName != nullptr)
		printf("%s begins:\n", testName);

	printf("The original list is:\n");
	PrintList(pHead);

	ComplexListNode* pClonedHead = Clone(pHead);

	printf("The cloned list is:\n");
	PrintList(pClonedHead);
}

//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//  |       |      /|\             /|\
//  --------+--------               |
//          -------------------------
void Test1()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, pNode3);
	BuildNodes(pNode2, pNode3, pNode5);
	BuildNodes(pNode3, pNode4, nullptr);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test1", pNode1);
}

// m_pSiblingָ��������
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//         |       | /|\           /|\
//         |       | --             |
//         |------------------------|
void Test2()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, nullptr);
	BuildNodes(pNode2, pNode3, pNode5);
	BuildNodes(pNode3, pNode4, pNode3);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test2", pNode1);
}

// m_pSibling�γɻ�
//          -----------------
//         \|/              |
//  1-------2-------3-------4-------5
//          |              /|\
//          |               |
//          |---------------|
void Test3()
{
	ComplexListNode* pNode1 = CreateNode(1);
	ComplexListNode* pNode2 = CreateNode(2);
	ComplexListNode* pNode3 = CreateNode(3);
	ComplexListNode* pNode4 = CreateNode(4);
	ComplexListNode* pNode5 = CreateNode(5);

	BuildNodes(pNode1, pNode2, nullptr);
	BuildNodes(pNode2, pNode3, pNode4);
	BuildNodes(pNode3, pNode4, nullptr);
	BuildNodes(pNode4, pNode5, pNode2);

	Test("Test3", pNode1);
}

// ֻ��һ�����
void Test4()
{
	ComplexListNode* pNode1 = CreateNode(1);
	BuildNodes(pNode1, nullptr, pNode1);

	Test("Test4", pNode1);
}

// ³���Բ���
void Test5()
{
	Test("Test5", nullptr);
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	system("pause");
	return 0;
}