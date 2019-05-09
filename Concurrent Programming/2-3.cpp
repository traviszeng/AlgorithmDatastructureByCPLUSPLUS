#include<iostream>
#include<thread>
#include <algorithm>
#include<vector>

void some_function();
void some_other_function();
std::thread t1(some_function); // 1
// std::thread t2 = t1; // 编译错误 线程对象之间是不能复制的，只能移动
std::thread t2 = std::move(t1); // 2
t1 = std::thread(some_other_function); // 3 隐式调用move
std::thread t3; // 4 
t3 = std::move(t2); // 5
t1.terminate();
t1 = std::move(t3); // 6 赋值操作将使程序崩溃 可以通过std::move()转移一个线程所有权给一个未关联线程的thread对象，但是不能通过赋一个新值的方式丢弃一个线程

//线程的所有权可以在函数外进行转移
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

//允许 std::thread 实例可作为参数进行传递
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
		threads.push_back(std::thread(do_work, i)); // 产生线程
	}
	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join)); // 对每个线程调用join()
}