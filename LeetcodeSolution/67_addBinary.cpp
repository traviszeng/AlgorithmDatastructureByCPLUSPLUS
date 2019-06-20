#include<string>
using namespace std;

string addBinary(string a, string b) {
	if (a=="")
		return b;
	if (b == "")
		return a;
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	int extra = 0;
	string result = "";
	int minSize = a.length() > b.length() ? b.length() : a.length();
	for(int i =0;i<minSize;i++){
		if (a[i] == '0' && b[i] == '0') {
			result += ('0' + extra);
			extra = 0;
		}
		else if ((a[i] == '1' &&b[i] == '0') || (a[i] == '0' && b[i] == '1')) {
			if (extra == 1) {
				result += '0';
				extra = 1;
			}

			else {
				extra = 0;
				result += '1';
			}
		}
		else {
			if (extra == 1) {
				result += '1';
			}
			else
				result += '0';
			extra = 1;
		}
	}
	if (a.length() == b.length() && extra == 1)
		result += '1';

	else if (a.length() > b.length()) {
		for (int i = minSize; i < a.length(); i++) 
		{
			if (extra == 0) {
				result += a.substr(i);
				break;
			}
 			else {
				if (a[i] == '0') {
					result += '1';
					extra = 0;
				}
				else {
					result += '0';
					extra = 1;
				}
			}
			
			
		}
		if (extra == 1)
			result += '1';
	}
	else {
		for (int i = minSize; i < b.length(); i++)
		{
			if (extra == 0) {
				result +=b.substr(i);
				break;
			}
			else {
				if (b[i] == '0') {
					result += '1';
					extra = 0;
				}
				else {
					result += '0';
					extra = 1;
				}
			}


		}
		if (extra == 1)
			result += '1';
	}
	reverse(result.begin(), result.end());
	return result;
}


int main() {
	string a = "1100000111111111100111101";
	string b = "11101110111111";
	addBinary(a, b);
}