#include<vector>
#include<string>

#include<iostream>
using namespace std;

bool isLongPressedName(string name, string typed) {
	int indiceName = 0;
	int indiceTyped = 0;
	while (indiceName<name.length()) {
		char a = name[indiceName];
		int countA = 1;
		while (name[indiceName + 1] == a)
		{
			countA++;
			indiceName++;

		}

		char b = typed[indiceTyped];
		if (b != a)
			return false;
		int countB = 1;
		while (typed[indiceTyped + 1] == b)
		{
			countB++;
			indiceTyped++;
		}
		if (countA>countB)
			return false;

		if (indiceName == name.length() - 1 && indiceTyped<typed.length() - 1)
			return false;

		indiceName++;
		indiceTyped++;
	}
	return true;
}


int main() {

	string a = "alexakiki";
	string b = "aaleexaaakkkkkikiiiiii";
	cout<<isLongPressedName(a, b);
	system("pause");

}