#include<iostream>
#include<thread>
#include <algorithm>
#include<vector>

void some_function();
void some_other_function();
std::thread t1(some_function); // 1
// std::thread t2 = t1; // ������� �̶߳���֮���ǲ��ܸ��Ƶģ�ֻ���ƶ�
std::thread t2 = std::move(t1); // 2
t1 = std::thread(some_other_function); // 3 ��ʽ����move
std::thread t3; // 4 
t3 = std::move(t2); // 5
t1.terminate();
t1 = std::move(t3); // 6 ��ֵ������ʹ������� ����ͨ��std::move()ת��һ���߳�����Ȩ��һ��δ�����̵߳�thread���󣬵��ǲ���ͨ����һ����ֵ�ķ�ʽ����һ���߳�

//�̵߳�����Ȩ�����ں��������ת��
std::thread f()
{
	void some_function();
	return std::thread(some_function);
}
std::thread g()
{
	void some_other_function(int);
	std::thread t(some_other_function, 42);
	return t;
}

//���� std::thread ʵ������Ϊ�������д���
void f(std::thread t);
void gg()
{
	void some_function();
	f(std::thread(some_function));
	std::thread t(some_function);
	f(std::move(t));
}


class scoped_thread
{
	std::thread t;
public:
	explicit scoped_thread(std::thread t_) : // 1
		t(std::move(t_))
	{
		if (!t.joinable()) // 2
			throw std::logic_error("No thread");
	}
	~scoped_thread()
	{
		t.join(); // 3
	}
	scoped_thread(scoped_thread const&) = delete;
	scoped_thread& operator=(scoped_thread const&) = delete;
};
struct func; 
void do_something_in_current_thread();
void ff()
{
	int some_local_state;
	scoped_thread t(std::thread(func(some_local_state))); // 4
	do_something_in_current_thread();
}

void do_work(unsigned id);
void f_autoAdd()
{
	std::vector<std::thread> threads;
	for (unsigned i = 0; i < 20; ++i)
	{
		threads.push_back(std::thread(do_work, i)); // �����߳�
	}
	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join)); // ��ÿ���̵߳���join()
}