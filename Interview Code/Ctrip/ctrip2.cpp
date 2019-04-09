#include<iostream>
#include<string>
using namespace std;

struct linkNode {
	int val;
	linkNode *next;
	
	linkNode(int value) {
		val = value;
	}
};
/*
linkNode *reverse(linkNode *head) {
	if (NULL == head || NULL == head->nextNodeNode) {
		return head;

	}
	linkNode *pNode;
	linkNode *pNewHead = NULL;
	while (head) {
		pNode = head;
		head = head->nextNodeNode;
		pNode->nextNodeNode = pNewHead;
		pNewHead = pNode;
	}
	return pNewHead;
}

linkNode *getLastNode(linkNode *head) {
	while (NULL != head->nextNodeNode) {
		head = head->nextNodeNode;
	}
	return head;
}*/


linkNode* reverseKGroup(linkNode* head, int k) {
	if (head == nullptr || head->next == nullptr)
		return head;
	linkNode *pHead = head;
	linkNode *pNewHead = head;
	linkNode *pCur = new linkNode(-1);
	int n = 0;
	while (1) {
		linkNode *pStart = pHead;
		linkNode *pEnd = pHead;
		if (pStart == nullptr || pStart->next == nullptr) break;
		linkNode *pNext = pStart->next;

		int kk = k;
		while (kk--)
		{
			if (pEnd != nullptr)
				pEnd = pEnd->next;
			else {
				pEnd = pStart;
				break;
			}
		}
		if (pEnd == pStart)
			break;
		kk = k;
		while (--kk) {
			pNext = pStart->next;
			pStart->next = pNext->next;
			pNext->next = pHead;
			pHead = pNext;

		}
		if (n == 0) {
			pNewHead = pHead;
			//pCur->next = pNewHead;
		}
		pCur->next = pHead;
		for (int i = 0; i < k; i++)
			pCur = pCur->next;

		n++;
		pHead = pEnd;
	}
	return pNewHead;

}


int main() {
	string linkList;
	cin >> linkList;
	linkNode *head = nullptr;
	linkNode *currentNode = nullptr;
	int listLen = 0;
	for (int i = 0; i < linkList.length(); i++) {
		if (linkList[i] == '[' || linkList[i] == ']' || linkList[i] == ',')
			continue;
		else {
			if (head == nullptr) {
				linkNode *temp = new linkNode(linkList[i]-'0');
				head = temp;
				currentNode = temp;
				listLen++;
			}
			else {
				linkNode *temp = new linkNode(linkList[i] - '0');
				currentNode->nextNode = temp;
				temp->preNode = currentNode;
				currentNode = temp;
				listLen++;
			}
		}
	}

	if (listLen == 0) return 0;
	int n;
	cin >> n;

	linkNode *newhead =reverseKGroup(head,n);
	cout << "[";
	linkNode *temp = newhead;
	while (temp) {
		cout << temp->val;
		if (temp->nextNode != nullptr) {
			cout << ",";
		}
		else { 
			cout << "]";
		}
	}


}