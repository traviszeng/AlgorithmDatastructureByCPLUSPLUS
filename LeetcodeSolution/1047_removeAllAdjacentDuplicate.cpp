#include<string>
using namespace std;

string removeDuplicates(string S) {
	bool isRemove = true;
	while (isRemove) {
		if (S.length() == 0 || S.length() == 1) {
			break;
		}

		for (int i = 1; i < S.length(); i++) {
			if (S[i] == S[i - 1])
			{
				S.erase(i - 1, 2);
				break;
			}
			if (i == S.length() - 1 && S[i] != S[i - 1])
				isRemove = false;
		}

	}
	return S;
}