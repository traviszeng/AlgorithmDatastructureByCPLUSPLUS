/**
Given an array A of integers, return true if and only if it is a valid mountain array.

Recall that A is a mountain array if and only if:

A.length >= 3
There exists some i with 0 < i < A.length - 1 such that:
A[0] < A[1] < ... A[i-1] < A[i]
A[i] > A[i+1] > ... > A[B.length - 1]

*/

#include<vector>
#include<iostream>
using namespace std;
bool validMountainArray(vector<int>& A) {
	if (A.size()<3)
		return false;
	//int indexOfMax = 0;
	int index = -1;
	for (int i = 0; i<A.size() - 1; i++) {
		if (A[i]>A[i + 1])
		{
			//indexOfMax+=1;
			index = i;
			break;
		}
	}
	if (index == 0 || index == -1)
		return false;
	for (int i = index; i<A.size() - 1; i++)
		if (A[i] <= A[i + 1])
			return false;
	return true;
}