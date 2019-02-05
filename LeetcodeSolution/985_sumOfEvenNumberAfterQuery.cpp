#include<iostream>
#include<vector>
using namespace std;

vector<int> sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries) {
	vector<int> result;
	for (int i = 0; i < queries.size(); i++) {
		A[queries[i][1]] += queries[i][0];
		int sum = 0;
		for (int j = 0; j < A.size(); j++)
			if (A[j] % 2 == 0)
				sum += A[j];
		result.push_back(sum);
	}
	return result;
		
}