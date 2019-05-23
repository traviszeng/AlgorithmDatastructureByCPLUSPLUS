#include</ReviewOfCPLUSPLUS/Data_Structure/ListRelated.h>
int main() {
	ListNode* head = new ListNode(3);
	head->next = new ListNode(1);
	head->next->next = new ListNode(4);
	head->next->next->next = new ListNode(2);
	head->next->next->next->next = new ListNode(-1);
	//MergeSort(head);
	printListNode(BubbleSort(head));
	system("pause");
}