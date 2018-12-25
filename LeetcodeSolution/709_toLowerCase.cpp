#include<string>
using namespace std;

/**
Implement function ToLowerCase() that has a string parameter str, and returns the same string in lowercase.



Example 1:

Input: "Hello"
Output: "hello"
Example 2:

Input: "here"
Output: "here"
Example 3:

Input: "LOVELY"
Output: "lovely"
*/

string toLowerCase(string str) {
	for (int i = 0; i<str.length(); i++) {
		if (int(str[i]) <= 90 && int(str[i]) >= 65)
		{
			str[i] = char(97 + int(str[i]) - 65);
		}

	}
	return str;
}