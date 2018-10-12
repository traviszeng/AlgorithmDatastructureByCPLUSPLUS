#pragma once
/*
�Զ�����������
*/
/*
�����ǵ�һ����֧�ֲ����ļ���
1.�������ʵ���������õ�������ʶ ���� ��֪���Լ��Ĵ�С
2.������֧������֮��ĸ�ֵ �Լ���������֮�����ȺͲ���ȵıȽϲ���
3.������Ӧ��֧�ֶ���������ֵ�������в�ѯ���� ��������Сֵ��ʲô ���ֵ��ʲô ĳ�������ֵ�Ƿ��������� ������� ��ռ�ĵ�һ��λ�õ�������ʲô
4.������֧�������� Ϊ�˱������� �ٶ�����һȺ�û� ������Ϊ����֧������Ĺ��ܺ���Ҫ ������һЩ�˶Դ�ȴ����ΪȻ
����֧��������� ������֧�����鱾��Ļ��� ����
5.�ܹ�ָ������ �Դ����������� ���ֵ�����ڱ���ʱ��֪��
6.�ܹ���һ��ֵ��ʼ������
7.�ܹ�ͨ��һ�����������������еĵ���Ԫ�� Ϊ�������� �����û�ǿ��Ҫ��������
�±��������ʵ�������
8.�ܹ��ػ�ָ�����������ֵ ����������Ϊ����б�Ҫ ����û��ѯ���û����뷨
������Ϊ����һ��������õ�����������ʵ�ֵ�
*/
class IntArray {

public:
	explicit IntArray(int sz = DefaultArraySize);
	IntArray(int *array, int array_size);
	IntArray(const IntArray &rhs);

	//�ع�
	void initData(int sz, int *array);

	bool operator==(const IntArray&) const;
	bool operator!=(const IntArray&) const;
	IntArray& operator=(const IntArray&);
	int size() const { return _size; }

	/*����Ϊ�麯������������ʵ����Ӧ����*/
	/**
	����������δʵ�ֵ��麯������main��ʵ��������Ҳ����麯����ʵ�� �������
	*/
	//ͨ��[]�����±�
	virtual int& operator[](int index);
	//virtual void sort();
	//virtual int min() const;
	//virtual int max() const;

	//���ֵ���������ҵ����򷵻ص�һ�γ��ֵ�����
	//���򷵻�-1
	//virtual int find(int value)const;

	~IntArray() {
		delete[]ia;
	}
	/*private:*/
	//����Ϊprotected������ɷ���
protected:
	//˽�д���
	int _size;
	int *ia;

	static const int DefaultArraySize = 12;
};

IntArray::IntArray(int sz) {
	//�������ݳ�Ա
	initData(sz, 0);

}

IntArray::IntArray( int *array, int sz) {
	initData(sz, array);
}

IntArray::IntArray(const IntArray &a) {
	initData(a._size, a.ia);
}

void IntArray::initData(int sz, int *array) {
	_size = sz;
	ia = new int[_size];
	for (int i = 0; i < _size; i++)
		if (!array)
			ia[i] = 0;
		else
			ia[i] = array[i];
}


int& IntArray::operator[](int index) {
	return ia[index];
}
