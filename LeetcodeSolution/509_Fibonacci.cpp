#include<iostream>
using namespace std;

int fib(int N) {
	if (N == 0)
		return 0;
	if (N == 1)
		return 1;
	
	int *pa = new int[N + 1];
	pa[0] = 0;
	pa[1] = 1;
	for (int i = 2; i < N + 1; i++)
		pa[i] = pa[i - 1] + pa[i - 2];
	return pa[N];
}