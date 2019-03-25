#include "BinaryTree.h"
#include<iostream>
#include<queue>

using namespace std;

void Print(BinaryTreeNode* pRoot)
{
	//用两个队列存放节点信息，每次清空一个队列，将其中节点的子节点存放到另外一个队列中
	if (pRoot == nullptr)
		return;
	queue<BinaryTreeNode*> nodeQueue;
	queue<BinaryTreeNode*> nodeQueue2;
	int flag = 1;
	nodeQueue.push(pRoot);
	while (!nodeQueue.empty() || !nodeQueue2.empty()) {
		if (flag == 1)
		{
			while (!nodeQueue.empty()) {
				BinaryTreeNode *temp = nodeQueue.front();
				nodeQueue.pop();
				cout << temp->m_nValue<<" ";
				if (temp->m_pLeft != nullptr) nodeQueue2.push(temp->m_pLeft);
				if (temp->m_pRight != nullptr) nodeQueue2.push(temp->m_pRight);
			}
			cout << endl;
			flag = 0;
		}
		else {
			while (!nodeQueue2.empty()) {
				BinaryTreeNode *temp = nodeQueue2.front();
				nodeQueue2.pop();
				cout << temp->m_nValue << " ";
				if (temp->m_pLeft != nullptr) nodeQueue.push(temp->m_pLeft);
				if (temp->m_pRight != nullptr) nodeQueue.push(temp->m_pRight);
			}
			cout << endl;
			flag = 1;
		
		}
	}
}


// ====================测试代码====================
//            8
//        6      10
//       5 7    9  11
void Test1()
{
	BinaryTreeNode* pNode8 = CreateBinaryTreeNode(8);
	BinaryTreeNode* pNode6 = CreateBinaryTreeNode(6);
	BinaryTreeNode* pNode10 = CreateBinaryTreeNode(10);
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode7 = CreateBinaryTreeNode(7);
	BinaryTreeNode* pNode9 = CreateBinaryTreeNode(9);
	BinaryTreeNode* pNode11 = CreateBinaryTreeNode(11);

	ConnectTreeNodes(pNode8, pNode6, pNode10);
	ConnectTreeNodes(pNode6, pNode5, pNode7);
	ConnectTreeNodes(pNode10, pNode9, pNode11);

	printf("====Test1 Begins: ====\n");
	printf("Expected Result is:\n");
	printf("8 \n");
	printf("6 10 \n");
	printf("5 7 9 11 \n\n");

	printf("Actual Result is: \n");
	Print(pNode8);
	printf("\n");

	DestroyTree(pNode8);
}

//            5
//          4
//        3
//      2
void Test2()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNode5, pNode4, nullptr);
	ConnectTreeNodes(pNode4, pNode3, nullptr);
	ConnectTreeNodes(pNode3, pNode2, nullptr);

	printf("====Test2 Begins: ====\n");
	printf("Expected Result is:\n");
	printf("5 \n");
	printf("4 \n");
	printf("3 \n");
	printf("2 \n\n");

	printf("Actual Result is: \n");
	Print(pNode5);
	printf("\n");

	DestroyTree(pNode5);
}

//        5
//         4
//          3
//           2
void Test3()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);
	BinaryTreeNode* pNode4 = CreateBinaryTreeNode(4);
	BinaryTreeNode* pNode3 = CreateBinaryTreeNode(3);
	BinaryTreeNode* pNode2 = CreateBinaryTreeNode(2);

	ConnectTreeNodes(pNode5, nullptr, pNode4);
	ConnectTreeNodes(pNode4, nullptr, pNode3);
	ConnectTreeNodes(pNode3, nullptr, pNode2);

	printf("====Test3 Begins: ====\n");
	printf("Expected Result is:\n");
	printf("5 \n");
	printf("4 \n");
	printf("3 \n");
	printf("2 \n\n");

	printf("Actual Result is: \n");
	Print(pNode5);
	printf("\n");

	DestroyTree(pNode5);
}

void Test4()
{
	BinaryTreeNode* pNode5 = CreateBinaryTreeNode(5);

	printf("====Test4 Begins: ====\n");
	printf("Expected Result is:\n");
	printf("5 \n\n");

	printf("Actual Result is: \n");
	Print(pNode5);
	printf("\n");

	DestroyTree(pNode5);
}

void Test5()
{
	printf("====Test5 Begins: ====\n");
	printf("Expected Result is:\n");

	printf("Actual Result is: \n");
	Print(nullptr);
	printf("\n");
}

//        100
//        /
//       50   
//         \
//         150
void Test6()
{
	BinaryTreeNode* pNode100 = CreateBinaryTreeNode(100);
	BinaryTreeNode* pNode50 = CreateBinaryTreeNode(50);
	BinaryTreeNode* pNode150 = CreateBinaryTreeNode(150);

	ConnectTreeNodes(pNode100, pNode50, nullptr);
	ConnectTreeNodes(pNode50, nullptr, pNode150);

	printf("====Test6 Begins: ====\n");
	printf("Expected Result is:\n");
	printf("100 \n");
	printf("50 \n");
	printf("150 \n\n");

	printf("Actual Result is: \n");
	Print(pNode100);
	printf("\n");
}

int main(int argc, char* argv[])
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	system("pause");
	return 0;
}