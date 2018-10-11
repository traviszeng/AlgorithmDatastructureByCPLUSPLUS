#include<iostream>
#include<string>
#include<vector>
#include <cassert>
#include<fstream>
using namespace std;

void read() { cout << "read()\n"; }
void sort() { cout << "sort()\n"; }
void compact() { cout << "compact()\n"; }
void write() { cout << "write()\n"; }

void partOne();


int main()
{
	partOne();
	

	system("pause");
	return 0;
}

void partOne() {
	read();
	sort();
	compact();
	write();
	vector<string> stringvec(20);
	string a = "helloworld";
	stringvec[0] = a;


	assert(a == stringvec[0]);//断言成功才会往下进行 否则给出诊断消息
	cout << "FILENAME:" << __FILE__ << endl << "Current line:" << __LINE__ << endl
		<< "Current time:" << __TIME__ << endl
		<< "Current date:" << __DATE__ << endl;

	ofstream outfile("out_file");
	ifstream infile("in_file");
	if (!infile) {
		cerr << "error: unable to open input file!\n";
		//return -1;
	}
	if (!outfile) {
		cerr << "error: unable to open output file!\n";
		//return -2;
	}
	string word;
	while (infile >> word)
		outfile << word << ' ';

	system("pause");
	//return 0;
}