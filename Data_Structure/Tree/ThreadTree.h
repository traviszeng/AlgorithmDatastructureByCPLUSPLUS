#pragma once
#ifndef THREADTREE
#define THREADTREE

// �����������Ľ����
template <typename T>struct ThreadNode {
	int ltag, rtag;	//������־
	ThreadNode<T> *leftChild, *rightChild; //��������Ůָ��
	T data;			//�������
	ThreadNode(const T item) {
		data = item;
		leftChild = NULL;
		rightChild = NULL;
		ltag = 0;
		rtag = 0;
	}
};

// ������������
template <typename T>class ThreadTree {
protected:
	ThreadNode<T> *root;
	void createInThread(ThreadNode<T> *current, ThreadNode<T> *& pre);
	ThreadNode<T> *parent(ThreadNode<T> *t);
public:
	ThreadTree() {
		root = NULL;
	}
	~ThreadTree() {
		destroy(root);
	}
	void InitThreadTree();
	void createInThread(); //������������������
	bool FindTh(const T &value);	//����������������value,�ɹ���true,����currentΪ�˽��;����false
	ThreadNode<T> *First(ThreadNode<T> *current);	//Ѱ�������µ�һ�����
	ThreadNode<T> *Last(ThreadNode<T> *current);	//Ѱ�����������һ�����
	ThreadNode<T> *Next(ThreadNode<T> *current);	//Ѱ�ҽ���������µĺ�̽��
	ThreadNode<T> *Prior(ThreadNode<T> *current);	//Ѱ�ҽ���������µ�ǰ�����
	void InOrder(void(*visit)(ThreadNode<T> *t));	//���������������������
	void PreOrder(void(*visit)(ThreadNode<T> *t));	//��������������ǰ�����
	void PostOrder(void(*visit)(ThreadNode<T> *t));	//�������������ĺ������	
	bool Find(const T &value);	//�ڳ������������value,�ɹ���true,����currentΪ�˽��;����false
	ThreadNode<T>* /*&*/ getCurrent() {//����current,����Ǹ���
		return current;
	}
	void destroy(ThreadNode<T> *& subTree);
private:
	ThreadNode<T> *current;
	bool Find(ThreadNode<T> *p, const T &value);			//����pΪ���ĳ��������������value
	bool setRoot(const T &rt) {                              //���ø�ֵΪrt
		root = new ThreadNode<T>(rt);
		if (root) return true;
		else return false;
	}
	static ThreadNode<T>* &leftChild(ThreadNode<T> *t) {//��������Ů
		return t->leftChild;
	}
	static ThreadNode<T>* &rightChild(ThreadNode<T> *t) {
		return t->rightChild;                //��������Ů
	}
	bool MakeLink(const T ex, const T ap, char linkmark);
	void Print(ThreadNode<T>* /*&*/p, int i);//p������Ϊ���ã�����ʵ��ָ��root���ƶ������ܱ����л��ƻ���
};
//-----------------------------------------------------------------------------------------------------------------
template <typename T>void ThreadTree<T>::destroy(ThreadNode<T> *& subTree) {//����Ӷ�����
	if (subTree != NULL) {
		destroy(subTree->leftChild);
		destroy(subTree->rightChild);
		delete subTree;
	}
}

template<typename T>bool ThreadTree<T>::Find(const T &value) {//�������������������ʹ��
	if (!root) {
		return 0;
	}
	else {
		return Find(root, value);
	}
}

template<typename T>bool ThreadTree<T>::Find(ThreadNode<T> *p, const T &value) {//����pΪ������������value
	if (!p) {
		return false;
	}
	if (p->data == value) {
		current = p;                 //�ҵ���currentָ��ý��
		return true;
	}
	else {
		return Find(p->leftChild, value) || Find(p->rightChild, value);//����ҵ��󲻻���ȥ�ұ�
	}
}


template<typename T>bool ThreadTree<T>::MakeLink(const T ex, const T ap, char linkmark) {//������ap����Ϊ������Ϊex������Ů
	if (linkmark != eptmark) {//������־		
		ThreadNode<T> *p = new ThreadNode<T>(ap);//��apת��Ϊ���
		if (Find(ex))                             //��ex,��Ϊcurrent
			cout << "cu " << current->data << endl;
		if (current) {
			switch (linkmark) {
			case 'l': current->leftChild = p;
				cout << "input success!" << endl; break;//��������Ů��ϵ
			case 'r': current->rightChild = p;
				cout << "input success!" << endl; break;//��������Ů��ϵ
			default: cout << "error! please reinput again!" << endl;
			}
			return false;//���ؼ٣�����
		}
		else {
			cout << "error! please reinput again!" << endl;
			return false;
		}
	}
	else return true;//�����棬����
}

template<typename T>void ThreadTree<T>::InitThreadTree() {
	cout << "please input the root node" << endl;//��������
	char elem1, elem2, elem3;
	cin >> elem1;
	while (1) {
		if (setRoot(elem1)) {
			cout << "input success!" << endl;
			break;
		}
		else cout << "error! please reinput again!" << endl;
	}
	cout << "please enter link between nodes, one existed and one to be inserted" << endl;
	cout << "e.g (Parent) (leftChild) l or (Parent) (rightChild) r" << endl;
	//�������������н�㣬Ҫ��elem1Ϊ�Ѽ���Ľ��
	//elem2Ϊ�½���㣬�Ҷ�����Ů��ϵ
	while (1) {
		cin >> elem1 >> elem2 >> elem3;//����ʽ����
		if (MakeLink(elem1, elem2, elem3)) break;//��������
	}
	cout << "treeview" << endl;
	Print(root, 0);
	return;
}

template<typename T>
void ThreadTree<T>::Print(ThreadNode<T>* /*&*/p, int i) {//ǰ�������ӡ
	if (p) {
		for (int j = 0; j < i; ++j) cout << '\t';	//iΪ�Ʊ������
		cout << p->data << endl;//�����ǰ���	    
		if (ThreadTree<T>::leftChild(p) || ThreadTree<T>::rightChild(p)) {//���󣬺���һ����Ȼ�������󣬵���Ҷ��ֹ
			++i;//���
			Print(ThreadTree<T>::leftChild(p), i);//�ݹ����������
			Print(ThreadTree<T>::rightChild(p), i);//�ݹ����������
		}
	}
	return;
}


template <typename T>void ThreadTree<T>::createInThread() {
	ThreadNode<T> *pre = NULL;		//ǰ�����ָ��
	if (/*!*/root) {					//��
		createInThread(root, pre);	//�������������������
		pre->rightChild = NULL;		//�����������һ�����
		pre->rtag = 1;
	}
}

//ͨ���������, �Զ���������������
template <typename T>void ThreadTree<T>::createInThread(ThreadNode<T> *current, ThreadNode<T> *& pre) {
	if (!current) {
		return;
	}
	createInThread(current->leftChild, pre); // ������������	
	if (current->leftChild == NULL) {         //������ǰ����ǰ������
		current->leftChild = pre;
		current->ltag = 1;
	}
	if (pre != NULL && pre->rightChild == NULL) {//����ǰ�����ĺ������
		pre->rightChild = current;
		pre->rtag = 1;
	}
	pre = current;//ǰ������,��ǰָ����ǰ����	
	createInThread(current->rightChild, pre);//�ݹ�, ������������
}

template <typename T>ThreadNode<T>* ThreadTree<T>::First(ThreadNode<T> *current) {// ������currentΪ������������ĵ�һ�����
	ThreadNode<T> *p = current;
	while (p->ltag == 0) {
		p = p->leftChild;//�����½�㣨��һ����Ҷ��㣩
	}
	return p;
}

template <typename T>ThreadNode<T> * ThreadTree <T>::Next(ThreadNode<T> *current) {// ���ؽ��current��������ĺ�̽��
	ThreadNode<T> *p = current->rightChild;
	if (current->rtag == 0) {	//rtag == 0, ��ʾ������Ů	
		return First(p);
	}
	else {	//rtag == 1, ֱ�ӷ��غ������	
		return p;
	}
}

template <typename T>ThreadNode<T> *ThreadTree<T>::Last(ThreadNode<T> *current) {// ������currentΪ����������������һ�����
	ThreadNode<T> *p = current;
	//�����½�㣨��һ����Ҷ��㣩
	while (p->rtag == 0) {
		p = p->rightChild;//�����½�㣨��һ����Ҷ��㣩
	}
	return p;
}

template <typename T>ThreadNode<T> *ThreadTree<T>::Prior(ThreadNode<T> *current) {// �������������ǰ�����
																				  //�������������������������н��current�������µ�ǰ����㡣
	ThreadNode<T> *p = current->leftChild;
	if (current->ltag == 0) {	//�������������������һ�����	
		return Last(p);
	}
	else { //ltag==1, ֱ�ӷ���ǰ������	
		return p;
	}
}
template<typename T>bool ThreadTree<T>::FindTh(const T &value) {//������������ʹ��
	ThreadNode<T> *p;
	for (p = First(root); p != NULL; p = Next(p)) {
		if (p->data == value) {
			current = p;
			return true;
		}
	}
	return false;
}

template <typename T>void ThreadTree <T>::InOrder(void(*visit)(ThreadNode<T> *t)) {//�������
	ThreadNode<T> *p;
	for (p = First(root); p != NULL; p = Next(p)) {
		visit(p);
	}
}

template <typename T>void ThreadTree<T>::PreOrder(void(*visit)(ThreadNode<T> *t)) {// ǰ�����
	ThreadNode<T> *p = root;
	while (p) {
		visit(p);				//���ʸ����
		if (p->ltag == 0) {		//������Ů,��Ϊ���		
			p = p->leftChild;
		}
		else if (p->rtag == 0) {	//������Ů,��Ϊ���		
			p = p->rightChild;
		}
		else {
			while (p != NULL && p->rtag == 1) {	//�غ���������,ֱ��������Ů�Ľ��			
				p = p->rightChild;
			}
			if (p != NULL) {	//����Ů��Ϊ���			
				p = p->rightChild;
			}
		}
	}
}

template <typename T>void ThreadTree<T>::PostOrder(void(*visit)(ThreadNode<T> *p)) {
	ThreadNode<T> *t = root;
	//Ѱ�Һ����һ�����
	while (t->ltag == 0 || t->rtag == 0) {
		if (t->ltag == 0) {
			t = t->leftChild;
		}
		else if (t->rtag == 0) {
			t = t->rightChild;
		}
	}
	visit(t);	//���ʵ�һ�����
	ThreadNode<T> *p;
	while ((p = parent(t)) != NULL) {
		if (p->rightChild == t || p->rtag == 1) {	//*t��*p�ĺ�����		
			t = p;
		}
		else {	//����t�Ƶ�*p��������		
			t = p->rightChild;
			while (t->ltag == 0 || t->rtag == 0) {
				if (t->ltag == 0) {
					t = t->leftChild;
				}
				else if (t->rtag == 0) {
					t = t->rightChild;
				}
			}
		}
		visit(t);
	}
}

template <typename T>ThreadNode<T> *ThreadTree<T>::parent(ThreadNode<T> *t) {
	ThreadNode<T> *p;
	if (t == root) {
		return NULL;
	}
	for (p = t; p->ltag == 0; p = p->leftChild);//��*tΪ��������һ����㣬��ǰ����*t������
	if (p->leftChild != NULL) {//��ָ����ǰ�������ý����ȫ��(tΪroot)�����һ������ǰ��
		p = p->leftChild;//�ҵ�����
		if (p->rightChild != t/*&&p->leftChild != t*/)//������Ǹ����
			for (p = p->rightChild; //����һ��
				/*rightChild != t&&*/p->leftChild != t;//��t�Ƿ�p����Ů������һ�����ҵ�
				p = p->leftChild);//�����ߵ���
	}
	else {//�ý����ȫ��(tΪroot)�����һ��㣬��ǰ�������뻻һ������ȥ�ұ��Һ��
		for (p = t; p->rtag == 0; p = p->rightChild);//��*tΪ���������һ�����
		p = p->rightChild;//�ҵ�����
		if (p->leftChild != t/*&&p->rightChild != t*/)
			for (p = p->leftChild;//����һ��
				/*p->leftChild != t&&*/p->rightChild != t;
				p = p->rightChild);//�����ߵ���,�����ҵ�
	}
	return p;
}
#endif