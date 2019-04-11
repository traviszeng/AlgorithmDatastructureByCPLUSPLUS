#include<iostream>
using namespace std;

int isPrime[1000];
int isPrimeKTimes[1000];
int main() {
	
	
	int n;
	cin >> n;
	int sum = 0;
	
	for (int i = 2; i <= n; i++) {
		if (!isPrime[i]) {
			for (int j = i + i; j <= n; j += i) 
				isPrime[j] = 1;
		}
	}
		
	for (int i = 2; i <= n; i++) {
		if (!isPrime[i]) {
			for (int j = i; j <= n; j *= i) 
				isPrimeKTimes[j] = 1;
		}
	}
	for (int i = 2; i <= n; i++) {
		if (isPrimeKTimes[i])
			sum++;
	}
	cout << sum ;
		
	
	return 0;
	
}