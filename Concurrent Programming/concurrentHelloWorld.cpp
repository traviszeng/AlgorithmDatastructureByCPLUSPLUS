#include<iostream>
#include<thread>
using namespace std;
void hello() { //每个线程必须要有一个初始函数，新线程的执行从这里开始
	std::cout << "hello Concurrent world" << endl;
}

struct func {
	int &i;
	func(int &i_) :i(i_) {}

	void operator()() {
		for (unsigned j = 0; j < 100000; j++) {
			//dosomething(i);  //悬空引用
		}
	}

};

void oops() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	my_thread.detach();		//无需等待线程结束即可结束 detach后就不是joinable的
	//my_thread.join();     //需要等待线程结束

}//oops完成后可能my_thread仍然在运行，而some_local_state已经销毁 dosomething(i)会调用已经销毁的变量


void f() {
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);

	try {
		//dosomethingInConcurrentThread();
	}
	catch (exception) {
		t.join();//防止线程运行后产生异常，在join调用之前抛出，这意味着这次调用会被跳过
		throw;
	}
	t.join();
}


//使用RAII（资源获取即初始化方式）等待线程完成
class thread_guard {
	std::thread& t;
public :
	explicit thread_guard(std::thread& t_) :t(t_) {}

	~thread_guard() {
		if (t.joinable()) {
			t.join();
		}
	}

	thread_guard(thread_guard const&) = delete;//3 拷贝构造和赋值函数被标记为delete 不让编译器自动生成
	thread_guard& operator=(thread_guard const&) = delete;//可能会弄丢已经加入的线程。现在任何给thread_guard赋值都会编译错误

};

void ff() {//f可以改写成
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	thread_guard g(t);
	
	//dosomethingInConcurrentThread();
	/**
		ff运行完毕，局部对象逆序销毁，即thread_guard g是第一个销毁的对象，
		此时线程会在析构函数中被加入到原始线程中，即便dosomething抛出异常，销毁仍然会发生
	*/
}

int main() {
	std::thread t(hello);//以hello函数作为其初始函数
	t.join();
}
