#include<vector>
#include<algorithm>

using namespace std;


//直观做法 但是对10000位的大数显然不行
vector<int> addToArrayForm1(vector<int>& A, int K) {
	vector<int> result;
	int i = 0;
	long long int num = 0;
	while (i<A.size()) {
		num *= 10;
		num += A[i];
		i++;
	}

	num = num + K;
	while (num != 0) {

		result.push_back(num % 10);
		num /= 10;
	}

	reverse(result.begin(), result.end());
	return result;
}

vector<int> addToArrayForm(vector<int>& A, int K) {
	int indice = 0;
	int SIZE = A.size();
	reverse(A.begin(), A.end());
	while (K != 0) {
		if (indice<SIZE) {
			A[indice] += K % 10;
			K = K / 10;
			indice++;
		}
		else {
			A.push_back(K % 10);
			K /= 10;
		}
	}
	for (int i = 0; i<A.size() - 1; i++)
		if (A[i] >= 10) {
			A[i + 1] += A[i] / 10;
			A[i] = A[i] % 10;
		}

	if (A[A.size() - 1] >= 10)
	{
		int digit = A[A.size() - 1] % 10;
		A.push_back(A[A.size() - 1] / 10);
		A[A.size() - 2] = digit;

	}

	reverse(A.begin(), A.end());
	return A;
}