/**
 definition of Linked list node
*/

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(nullptr) {}
};

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	if (headA == nullptr || headB == nullptr)
		return nullptr;
	ListNode* tempA = headA;
	ListNode* tempB = headB;
	bool flagA = false;
	bool flagB = false;
	
	while (tempA != tempB) {
		if (tempA == nullptr && !flagA) {
			flagA = true;
			tempA = headB;
		}
		else {
			tempA = tempA->next;
		}


		if (tempB == nullptr && !flagB) {
			flagB = true;
			tempB = headA;
		}
		else {
			tempB = tempB->next;
		}
	}

	

	if (tempA == tempB &&tempA!=nullptr)
		return tempA;
	return nullptr;
}