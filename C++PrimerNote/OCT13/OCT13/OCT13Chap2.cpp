#include<iostream>
#include "Array.h"
#include "ArrayRC.h"
using namespace std;

template<class elemType>
void swap(Array<elemType> &array, int i, int j) {
	elemType tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
}

int main() {
	const int array_size = 4;

	/*Array<int> ia(array_size);

	Array<double> da(array_size);

	Array<char> ca(array_size);
	int ix;

	for (ix = 0; ix < array_size; ix++) {
		ia[ix] = ix;
		da[ix] = ix * 1.75;
		ca[ix] = ix + 'a';
	}
	for(ix = 0; ix < array_size; ix++) {
		cout << ia[ix] << endl;
		cout << da[ix] << endl;
		cout << ca[ix] << endl;
	}

	ArrayRC<int> ia_rc(10);*/

	Array<int> ia1;
	ArrayRC<int> ia2;
	cout << "swap() with Array<int> ia1\n";
	int size = ia1.size();
	swap(ia1, 1, size);
	cout << "swap() with ArrayRC<int> ia2\n";
	size = ia2.size();
	swap(ia2, 1, size);

	system("pause");
}