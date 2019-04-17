#include<iostream>
#include<vector>
#include<map>
#include<string>

using namespace std;
vector<string> uncommonFromSentences(string A, string B) {
	vector<string> result;
	map<string,int> wordDictA;
	string temp = "";
	for (int i = 0; i < A.length(); i++) {
		if (A[i] == ' ') {
			if (wordDictA.find(temp) != wordDictA.end()) {
				wordDictA[temp] += 1;
			}
			else {
				wordDictA[temp] = 1;
			}
			temp = "";
		}
		else {
			temp += A[i];
		}
	}
	if (wordDictA.find(temp) != wordDictA.end()) {
		wordDictA[temp] += 1;
	}
	else {
		wordDictA[temp] = 1;
	}



	map<string, int> wordDictB;
	temp = "";
	for (int i = 0; i < B.length(); i++) {
		if (B[i] == ' ') {
			if (wordDictB.find(temp) != wordDictB.end()) {
				wordDictB[temp] += 1;
			}
			else {
				wordDictB[temp] = 1;
			}
			temp = "";
		}
		else {
			temp += B[i];
		}
	}
	if (wordDictB.find(temp) != wordDictB.end()) {
		wordDictB[temp] += 1;
	}
	else {
		wordDictB[temp] = 1;
	}

	for (map<string, int>::iterator iter = wordDictA.begin(); iter != wordDictA.end(); iter++) {
		if (wordDictB.find(iter->first) == wordDictB.end() && iter->second == 1)
			result.push_back(iter->first);
	}
	for (map<string, int>::iterator iter = wordDictB.begin(); iter != wordDictB.end(); iter++) {
		if (wordDictA.find(iter->first) == wordDictA.end() && iter->second == 1)
			result.push_back(iter->first);
	}
	return result;
}