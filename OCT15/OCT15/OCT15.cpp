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

	//pi 被初始化为 "没有指向任何对象"
	int *pi = 0;

	// pi2 被初始化为 ival 的地址 
	int *pi2 = &val;

	// ok: pi 和 pi2 现在都指向 ival 
	pi = pi2;
	// 现在 pi2 没有指向任何对象
	pi2 = 0;

	double ival = 2.22;
	double *pd = &ival;

	/**当然 如果我们要做的仅仅是持有地址值 可能是把一个地址同另一个地址作比较
	那么指针的实际类型就不重要了 C++提供了一种特殊的指针类型来支持这种需求 空
	void* 类型指针 它可以被任何数据指针类型的地址值赋值 函数指针不能赋值给它*/
	/**void*表明相关的值是个地址 但该地址的对象类型不知道 我们不能够操作空类型指针
	所指向的对象 只能传送该地址值或将它与其他地址值作比较*/
	void *pv = pi;
	pv = pd;


	const char *st = "The expense of spirit\n";
	while (*st++) {
		cout << endl << *st;
	}

	string s1;
	const char *pc = "a character array";
	s1 = pc; // ok

	//char *str = s1; // 编译时刻类型错误
	//char *str = s1.c_str(); // 几乎是正确的 但是还差一点
	const char *str1 = s1.c_str();//ok

	string str("fa.disney.com");

	/*int size = str.size();
	for (int ix = 0; ix < size; ++ix)
		if (str[ix] == '.')
			str[ix] = '_';*/
	//与上面代码段功效相同 泛型算法
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