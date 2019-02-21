#include<string>
#include<iostream>
using namespace std;

bool checkRecord(string s) {
	int continueL = 0;
	int numOfA = 0;
	for (int i = 0; i<s.length(); i++)
	{
		if (s[i] == 'A')
			numOfA++;
		if (numOfA>1)
			return false;
		if (s[i] == 'L') {
			continueL++;
			if (continueL>2)
				return false;
		}
		else
			continueL = 0;
	}
	return true;
}