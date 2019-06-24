#include<string>
#include<iostream>
using namespace std;
string decodeAtIndex(string S, int K) {
	string result = "";
	int lo = 0;
	while (lo < S.length()) {
		
		if (S[lo] <= '9' && S[lo] >= '0') {
			int times = S[lo] - '0';
			S.erase(lo, 1);
			string sub = S.substr(0, lo);
			for (int i = 0; i < times-1; i++) {
				S.insert(lo, sub);
				lo += sub.length();
				if (lo > K)
					return result+S[K-1];
			}
		}
		else
			lo++;
	}
	return result + S[K-1];
}

int main(){

	string a = "a2b3c4d5e6f7g8h9";
	int K = 69280;
	cout<<decodeAtIndex(a, K)<<endl;
	system("pause");
}