#include<iostream>
#include<cstring>
#include<string>
#include<algorithm>

using namespace std;

int string_len(const char *st) {
	int cnt = 0;
	if (st)
		while (*st++)
			++cnt;
	return cnt;
}

int main() {
	int val = 1024;

	//pi ����ʼ��Ϊ "û��ָ���κζ���"
	int *pi = 0;

	// pi2 ����ʼ��Ϊ ival �ĵ�ַ 
	int *pi2 = &val;

	// ok: pi �� pi2 ���ڶ�ָ�� ival 
	pi = pi2;
	// ���� pi2 û��ָ���κζ���
	pi2 = 0;

	double ival = 2.22;
	double *pd = &ival;

	/**��Ȼ �������Ҫ���Ľ����ǳ��е�ֵַ �����ǰ�һ����ַͬ��һ����ַ���Ƚ�
	��ôָ���ʵ�����;Ͳ���Ҫ�� C++�ṩ��һ�������ָ��������֧���������� ��
	void* ����ָ�� �����Ա��κ�����ָ�����͵ĵ�ֵַ��ֵ ����ָ�벻�ܸ�ֵ����*/
	/**void*������ص�ֵ�Ǹ���ַ ���õ�ַ�Ķ������Ͳ�֪�� ���ǲ��ܹ�����������ָ��
	��ָ��Ķ��� ֻ�ܴ��͸õ�ֵַ������������ֵַ���Ƚ�*/
	void *pv = pi;
	pv = pd;


	const char *st = "The expense of spirit\n";
	while (*st++) {
		cout << endl << *st;
	}

	string s1;
	const char *pc = "a character array";
	s1 = pc; // ok

	//char *str = s1; // ����ʱ�����ʹ���
	//char *str = s1.c_str(); // ��������ȷ�� ���ǻ���һ��
	const char *str1 = s1.c_str();//ok

	string str("fa.disney.com");

	/*int size = str.size();
	for (int ix = 0; ix < size; ++ix)
		if (str[ix] == '.')
			str[ix] = '_';*/
	//���������ι�Ч��ͬ �����㷨
	replace(str.begin(), str.end(), '.', '_');




	system("pause");
	
	/*
	// ***** C-style character string implementation ***** 
		#include <iostream> 
		#include <cstring> 
		int main() 
		{ 
		  int errors = 0; 
		  const char *pc = "a very long literal string"; 
		  for ( int ix = 0; ix < 1000000; ++ix ) 
		  { 
		  int len = strlen( pc ); 
		  char *pc2 = new char[ len + 1 ]; 
		  strcpy( pc2, pc ); 
		  if ( strcmp( pc2, pc )) 
		  ++errors; 
		  delete [] pc2; 
		  } 
		  cout << "C-style character strings: " 
		  << errors << " errors occurred.\n"; 
		} 
	// ***** string implementation ***** 
		#include <iostream> 
		#include <string> 
		int main() { 
		  int errors = 0; 
		  string str( "a very long literal string" ); 
		  for ( int ix = 0; ix < 1000000; ++ix ) 
		  { 
		  int len = str.size(); 
		  string str2 = str; 
		  if ( str != str2 ) 
		  ++errors; 
		  } 
		  cout << "string class: " 
		  << errors << " errors occurred.\n";
		  }**/
}