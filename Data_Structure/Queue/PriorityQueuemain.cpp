#include <fstream>
#include <cassert>
#include "PriorityQueue.h"
using namespace std;

int main() {
	ifstream fin("data.txt");
	assert(fin);
	PriorityQueue<int> que;
	int data;
	while (!fin.eof()) {
		assert(fin >> data);
		que.EnQueue(data);
	}
	cout << "The queue in the file is:\n" << que << endl;
	que.getFront(data);
	cout << "The front in the queue is: " << data << endl;

	cout << "Delete the front in turn, the result is:" << endl;
	int len = que.getSize();
	for (int i = 0; i < len; i++) {
		que.DeQueue(data);
		cout << "Delete " << data << ", then the queue is:\n";
		cout << que << endl;
	}
	system("pause");
	return 0;
}