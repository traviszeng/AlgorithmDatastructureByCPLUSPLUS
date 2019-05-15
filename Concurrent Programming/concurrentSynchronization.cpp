#include<mutex>
#include<queue>

bool flag;
std::mutex m;
void wait_for_flag()
{
	std::unique_lock<std::mutex> lk(m);
	while (!flag)
	{
		lk.unlock(); // 1 解锁互斥量
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 2 休眠100ms
		lk.lock(); // 3 再锁互斥量
	}
}

/**在休眠前②，函数对互斥量进行解锁①，并且在休眠结束后再对互斥量进行上
锁，所以另外的线程就有机会获取锁并设置标识。*/


//4.1  使用 std::condition_variable 处理数据等待
typedef int data_chunk;
std::mutex mut;
std::queue<data_chunk> data_queue; // 1
std::condition_variable data_cond;
void data_preparation_thread()
{
	while (more_data_to_prepare())
	{
		data_chunk const data = prepare_data();
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(data); // 2
		data_cond.notify_one(); // 3
	}
}
void data_processing_thread()
{
	while (true)
	{
		std::unique_lock<std::mutex> lk(mut); // 4
		data_cond.wait(
			lk, [] {return !data_queue.empty(); }); // 5
		data_chunk data = data_queue.front();
		data_queue.pop();
		lk.unlock(); // 6
		process(data);
		if (is_last_chunk(data))
			break;
	}
}

//4.5 线程安全的队列
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
template<typename T>
class threadsafe_queue
{
private:
	mutable std::mutex mut; // 1 互斥量必须是可变的
	/*如果锁住互斥量是一个可变操作，那么这个互斥量对象就会标记为可变的①，之后他就
可以在empty()和拷贝构造函数中上锁了*/
	std::queue<T> data_queue;
	std::condition_variable data_cond;
public:
	threadsafe_queue()
	{}
	threadsafe_queue(threadsafe_queue const& other)
	{
		
		std::lock_guard<std::mutex> lk(other.mut); //保证此时other锁住
		data_queue = other.data_queue;
	}
	void push(T new_value)
	{
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(new_value);
		data_cond.notify_one();
	}
	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		value = data_queue.front();
		data_queue.pop();
	}
	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		std::shared_ptr<T> res(std::make_shared<T>(data_queue.front())); //make_shared 在动态内存中分配一个对象并初始化它，返回指向此对象的shared_ptr
		data_queue.pop();
		return res;
	}
	bool try_pop(T& value)
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return false;
		value = data_queue.front();
		data_queue.pop();
		return true;
	}
	std::shared_ptr<T> try_pop()
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return std::shared_ptr<T>();
		std::shared_ptr<T> res(std::make_shared<T>(data_queue.front()));
		data_queue.pop();
		return res;
	}
	bool empty() const
	{
		std::lock_guard<std::mutex> lk(mut);
		return data_queue.empty();
	}
};

//4.6 使用 std::future 从异步任务中获取返回值
#include <future>
#include <iostream>
int find_the_answer_to_ltuae();
void do_other_stuff();
int main()
{
	std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
	do_other_stuff();
	std::cout << "The answer is " << the_answer.get() << std::endl;
}


//4.7 
#include <string>
struct X
{
	void foo(int, std::string const&);
	std::string bar(std::string const&);
};
X x;
auto f1 = std::async(&X::foo, &x, 42, "hello"); // 调用p->foo(42, "hello")，p是指向x的指针
auto f2 = std::async(&X::bar, x, "goodbye"); // 调用tmpx.bar("goodbye")， tmpx是x的拷贝副本
struct Y
{
	double operator()(double);
};

void maintest() {
	Y y;
	auto f3 = std::async(Y(), 3.141); // 调用tmpy(3.141)，tmpy通过Y的移动构造函数得到
	auto f4 = std::async(std::ref(y), 2.718); // 调用y(2.718)
	X baz(X&);
	std::async(baz, std::ref(x)); // 调用baz(x)
}

class move_only
{
public:
	move_only();
	move_only(move_only&&);
	move_only(move_only const&) = delete;
	move_only& operator=(move_only&&);
	move_only& operator=(move_only const&) = delete;
	void operator()();
};
auto f5 = std::async(move_only()); // 调用tmp()，tmp是通过std::move(move_only())构造得到