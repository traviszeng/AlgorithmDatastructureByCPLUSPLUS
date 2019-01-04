#include<vector>
#include<iostream>

using namespace std;
vector<int> sortArrayByParityII(vector<int> &A) {
	if (A.size() <= 0) {
		return A;
	}
	
	int oddFlag = 1;
	int evenFlag = 0;

	while (oddFlag < A.size() && evenFlag < A.size()) {
		while (A[oddFlag] & 0x1)
			oddFlag+=2;
		while(!(A[evenFlag] & 0x1) )
			evenFlag+=2;
		if (oddFlag < A.size() && evenFlag < A.size())
		{
			swap(A[evenFlag], A[oddFlag]);
			oddFlag += 2;
			evenFlag += 2;
		}
	}

	return A;
}

int main() {
	
	vector<int> A;
	A.push_back(4);
	A.push_back(2);
	A.push_back(5);
	A.push_back(7);
	A.push_back(7);
	A.push_back(1);
	A.push_back(6);
	A.push_back(8);
	sortArrayByParityII(A);
	for (int i = 0; i < A.size(); i++)
		cout << A[i] << " ";
	system("pause");
}