#include<iostream>
using namespace std;

void Permutation(char* pStr, char* pBegin);

void Permutation(char* pStr)
{
	if (pStr == nullptr)
		return;
	Permutation(pStr, pStr);
}

void Permutation(char* pStr, char* pBegin) {
	if (*pBegin == '\0') {
		cout << pStr<<endl;
	}
	else {
		for (char *p = pBegin; *p != '\0'; p++) {
			char temp = *pBegin;
			*pBegin = *p;
			*p = temp;

			Permutation(pStr, pBegin + 1);

			temp = *pBegin;
			*pBegin = *p;
			*p = temp;

		}
	}
}

// ====================²âÊÔ´úÂë====================
void Test(char* pStr)
{
	if (pStr == nullptr)
		printf("Test for nullptr begins:\n");
	else
		printf("Test for %s begins:\n", pStr);

	Permutation(pStr);

	printf("\n");
}

int main(int argc, char* argv[])
{
	Test(nullptr);

	char string1[] = "";
	Test(string1);

	char string2[] = "a";
	Test(string2);

	char string3[] = "ab";
	Test(string3);

	char string4[] = "abc";
	Test(string4);
	system("pause");
	return 0;
}