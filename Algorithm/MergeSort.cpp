#include<iostream>
using namespace std;

void merge(int *a, int start, int end, int *t) {
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	int start1 = start;
	int start2 = mid + 1;
	int end1 = mid;
	int end2 = end;
	merge(a, start1, end1, t);
	merge(a, start2, end2, t);

	int k = start;
	while (start1 <= end1 && start2 <= end2) {
		t[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
	}

	while (start1 <= end1)
		t[k++] = a[start1++];
	while (start2 <= end2)
		t[k++] = a[start2++];

	for (int i = start; i <=end; i++) {
		a[i] = t[i];
		cout << a[i]<<" ";
	}
	cout << endl;
}

void mergeSort(int* a, int len) {
	if (len == 0)
		return;
	int *t = new int[len];
	merge(a, 0, len - 1,t);
	delete[] t;
}


int main() {
	int a[10] = { 9,8,7,6,5,4,1,2,3,10 };
	mergeSort(a, 10);
	for (int i = 0; i < 10; i++) {
		cout << a[i] << " " ;
	}
	system("pause");

}