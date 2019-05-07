#include<iostream>
#include<thread>
using namespace std;
void hello() { //ÿ���̱߳���Ҫ��һ����ʼ���������̵߳�ִ�д����￪ʼ
	std::cout << "hello Concurrent world" << endl;
}

struct func {
	int &i;
	func(int &i_) :i(i_) {}

	void operator()() {
		for (unsigned j = 0; j < 100000; j++) {
			//dosomething(i);  //��������
		}
	}

};

void oops() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	my_thread.detach();		//����ȴ��߳̽������ɽ��� detach��Ͳ���joinable��
	//my_thread.join();     //��Ҫ�ȴ��߳̽���

}//oops��ɺ����my_thread��Ȼ�����У���some_local_state�Ѿ����� dosomething(i)������Ѿ����ٵı���


void f() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);

	try {
		//dosomethingInConcurrentThread();
	}
	catch (exception) {
		t.join();//��ֹ�߳����к�����쳣����join����֮ǰ�׳�������ζ����ε��ûᱻ����
		throw;
	}
	t.join();
}


//ʹ��RAII����Դ��ȡ����ʼ����ʽ���ȴ��߳����
class thread_guard {
	std::thread& t;
public :
	explicit thread_guard(std::thread& t_) :t(t_) {}

	~thread_guard() {
		if (t.joinable()) {
			t.join();
		}
	}

	thread_guard(thread_guard const&) = delete;//3 ��������͸�ֵ���������Ϊdelete ���ñ������Զ�����
	thread_guard& operator=(thread_guard const&) = delete;//���ܻ�Ū���Ѿ�������̡߳������κθ�thread_guard��ֵ����������

};

void ff() {//f���Ը�д��
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	
	//dosomethingInConcurrentThread();
	/**
		ff������ϣ��ֲ������������٣���thread_guard g�ǵ�һ�����ٵĶ���
		��ʱ�̻߳������������б����뵽ԭʼ�߳��У�����dosomething�׳��쳣��������Ȼ�ᷢ��
	*/
}

int main() {
	std::thread t(hello);//��hello������Ϊ���ʼ����
	t.join();
}
