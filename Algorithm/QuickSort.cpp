#include<iostream>

using namespace std;

// ¿ìËÙÅÅĞò£¨µİ¹é£©
void QuickSort(int *a,int start,int end) {
	if (start >= end)
		return;
	int key = a[start];
	int originStart = start;
	int originEnd = end;
	while (start < end) {
		//int k = end;
		while (start < end && a[end] >= key)
			end--;
		if (start < end) {
			a[start] = a[end];
		}

		while (start < end && a[start] <= key)
			start++;
		if (start < end)
			a[end] = a[start];
	}
	a[start] = key;
	QuickSort(a, originStart, start);
	QuickSort(a,start+1, originEnd);

}


int main() {
	int a[10] = { 9,8,7,6,5,4,1,2,3,10 };
	QuickSort(a, 0,9);
	for (int i = 0; i < 10; i++) {
		cout << a[i] << " ";
	}
	system("pause");

}
