#include<iostream>
using namespace std;
int main() {
	int fib[] = { 1,2,2,3,4,5,6 };
	for (int i = 0; i < sizeof(fib)/sizeof(fib[0]); i++) {
		cout << fib[i] << endl;
	}

	int val = 1024;
	int val2 = val + 1;
	int *point = &val;

	
	system("pause");

	return 0;
}