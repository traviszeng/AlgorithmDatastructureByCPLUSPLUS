#include<string>
using namespace std;
/*Brutal force MLE memory limit exceed
	string decodeAtIndex(string S, int K) {
		string result = "";
		int lo = 0;
		while (lo < S.length()) {

			if (S[lo] <= '9' && S[lo] >= '0') {
				int times = S[lo] - '0';
				S.erase(lo, 1);
				string sub = S.substr(0, lo);
				for (int i = 0; i < times - 1; i++) {
					S.insert(lo, sub);
					lo += sub.length();
					if (lo > K)
						return result + S[K - 1];
				}
			}
			else
				lo++;
		}
		return result + S[K - 1];
	}
*/

string decodeAtIndex(string S, int K) {
	long size = 0;
	int N = S.size();

	// Find size = length of decoded string
	for (int i = 0; i < N; ++i) {
		if (isdigit(S[i]))
			size *= S[i] - '0';
		else
			size++;
	}

	for (int i = N - 1; i >= 0; --i) {
		K %= size;
		if (K == 0 && isalpha(S[i]))
			return (string) "" + S[i];

		if (isdigit(S[i]))
			size /= S[i] - '0';
		else
			size--;
	}
	return "";
}

int main() {
	string a = "czjkk9elaqwiz7s6kgvl4gjixan3ky7jfdg3kyop3husw3fm289thisef8blt7a7zr5v5lhxqpntenvxnmlq7l34ay3jaayikjps";
	long N = 768077956;
	decodeAtIndex(a, N);
}