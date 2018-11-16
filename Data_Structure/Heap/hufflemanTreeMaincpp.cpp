#include <fstream>
#include <cassert>
#include "HuffmanTree.h"
#include "MinHeap2.h"
using namespace std;
int main() {
	ifstream fin("heapData.txt");
	assert(fin);
	int n, i;
	assert(fin >> n);
	int * w = new int[n + 1];
	cout << "There are " << n << " nodes in the file.\n";
	cout << "The weight of each node is:\n";
	for (i = 1; i <= n; i++) {
		fin >> w[i];
		cout << "weight[" << i << "]: " << w[i] << endl;
	}
	cout << "\nCreate huffman tree:\n";
	HuffmanTree<int, int> htree(w, n);
	cout << endl;
	delete w;
	cout << "Press enter to exit!\n";
	char ch;
	cin.get(ch);
	return 0;
}