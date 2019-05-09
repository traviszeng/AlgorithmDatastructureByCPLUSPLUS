#include<deque>
#include<list>
#include<mutex>
#include<algorithm>
#include <exception>
#include <memory>
#include <mutex>
#include <stack>

//3.1

std::list<int> some_list; // 1 被全局的互斥量some_mutex保护
std::mutex some_mutex; // 2
void add_to_list(int new_value)
{
	std::lock_guard<std::mutex> guard(some_mutex); // 3使用lock_guard不用手动写mutex.unlock() 析构guard时会自动调用unlock() 防止异常产生时没有unlock
	some_list.push_back(new_value);
}
bool list_contains(int value_to_find)
{
	std::lock_guard<std::mutex> guard(some_mutex); // 4
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end()
		;
}

//add_to_list和list_contains互斥，对数据的访问是互斥的；list_contains()不可能看到正在被add_to_list()修改的列表
/**当其中一个成员函数返回的是保护数据的指针或引用时，会破坏对数据的保护。
具有访问能力的指针或引用可以访问(并可能修改)被保护的数据，而不会被互斥锁限制。*/

//3.2 an example 
class some_data
{
	int a;
	std::string b;
public:
	void do_something();
};
class data_wrapper
{
private:
	some_data data;
	std::mutex m;
public:
	template<typename Function>
	void process_data(Function func)
	{
		std::lock_guard<std::mutex> l(m);
		func(data); // 1 传递“保护”数据给用户函数
	}
};
some_data* unprotected;
void malicious_function(some_data& protected_data)
{
	unprotected = &protected_data;
}
data_wrapper x;
void foo()
{
	x.process_data(malicious_function); // 2 传递一个恶意函数
	unprotected->do_something(); // 3 在无保护的情况下访问保护数据
}

//3.3
template<typename T, typename Container = std::deque<T> >
class stack
{
public:
	explicit stack(const Container&);
	explicit stack(Container&& = Container());
	template <class Alloc> explicit stack(const Alloc&);
	template <class Alloc> stack(const Container&, const Alloc&);
	template <class Alloc> stack(Container&&, const Alloc&);
	template <class Alloc> stack(stack&&, const Alloc&);
	bool empty() const;
	size_t size() const;
	T& top();
	T const& top() const;
	void push(T const&);
	void push(T&&);
	void pop();
	void swap(stack&&);
};


//3.4
/*#include <exception>
#include <memory> // For std::shared_ptr<>
struct empty_stack : std::exception
{
	const char* what() const throw() {};
};
template<typename T>
class threadsafe_stack
{
public:
	threadsafe_stack();
	threadsafe_stack(const threadsafe_stack&);
	threadsafe_stack& operator=(const threadsafe_stack&) = delete; // 1 赋值操作被删除
	void push(T new_value);
	std::shared_ptr<T> pop(); //shared_ptr不仅能避免内存泄露(因为当对象中指针销毁时，对象也会被销毁)，而且标准库能够完全控制内存分配方案，也就不需要new和delete操作
	void pop(T& value); //pop的时候使用一个局部引用去存储弹出值，并返回一个std::shared_ptr<>对象
	bool empty() const;
};*/

//3.5 线程安全堆栈具体实现

struct empty_stack : std::exception
{
	const char* what() const throw() {
		return "empty stack!";
	};
};
template<typename T>
class threadsafe_stack
{
private:
	std::stack<T> data;
	mutable std::mutex m; //有些时候，我们需要在const的函数里面修改一些跟类状态无关的数据成员，那么这个数据成员就应该被mutalbe来修饰
public:
	threadsafe_stack()
		: data(std::stack<int>()) {}
	threadsafe_stack(const threadsafe_stack& other)
	{
		std::lock_guard<std::mutex> lock(other.m);
		data = other.data; // 1 在构造函数体中的执行拷贝
	}
	threadsafe_stack& operator=(const threadsafe_stack&) = delete;
	void push(T new_value)
	{
		std::lock_guard<std::mutex> lock(m);
		data.push(new_value);
	}
	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack(); // 在调用pop前，检查栈是否为空
		std::shared_ptr<T> const res(std::make_shared<T>(data.top())); // 在修改堆栈前，分配出返回值
			data.pop();
		return res;
	}
	void pop(T& value)
	{
		std::lock_guard<std::mutex> lock(m);
		if (data.empty()) throw empty_stack();
		value = data.top();
		data.pop();
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}
};

//预防死锁 （多个互斥量之间相互等待）
//避免死锁的一般建议，就是让两个互斥量总以相同的顺序上锁
/*C++标准库有办法解决这个问题， std::lock ——可以一次性锁住多个(两个以上)的
互斥量，并且没有副作用(死锁风险)*/

//3.6

// 这里的std::lock()需要包含<mutex>头文件
class some_big_object {};
void swap(some_big_object& lhs, some_big_object& rhs);
class X
{
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(some_big_object const& sd) :some_detail(sd) {}
	friend void swap(X& lhs, X& rhs)
	{
		if (&lhs == &rhs)
			return;
		std::lock(lhs.m, rhs.m); // 1 要么两个都锁住，要么一个都不锁
		/**提供 std::adopt_lock 参数除了表示 std::lock_guard 对象已经上锁外，还表示现成
		的锁，而非尝试创建新的锁。*/
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock); // 2
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock); // 3
		swap(lhs.some_detail, rhs.some_detail);
	}

};


//3.8 层次锁的实现
/**尽管它是一个用户定义类型，它可以用于 std::lock_guard<> 模板中，因为它的
实现有三个成员函数为了满足互斥量操作：lock(), unlock() 和 try_lock()*/
class hierarchical_mutex
{
	std::mutex internal_mutex;
	unsigned long const hierarchy_value;
	unsigned long previous_hierarchy_value;
	/**因为其声明中有thread_local，所以每个线程都有其拷贝副本，这样线程中变量状态完全独立，
当从另一个线程进行读取时，变量的状态也完全独立*/
	static thread_local unsigned long this_thread_hierarchy_value; // 1 是使用了thread_local的值来代表当前线程的层级值：this_thread_hierarchy_value
																   //它被初始化为最大值⑧，所以最初所有线程都能被锁住
	void check_for_hierarchy_violation()
	{
		if (this_thread_hierarchy_value <= hierarchy_value) // 2
		{
			throw std::logic_error("mutex hierarchy violated");
		}
	}
	void update_hierarchy_value() //更新层级值
	{
		previous_hierarchy_value = this_thread_hierarchy_value; // 3
		this_thread_hierarchy_value = hierarchy_value;
	}
public:
	explicit hierarchical_mutex(unsigned long value) :
		hierarchy_value(value),
		previous_hierarchy_value(0)
	{}
	void lock()
	{
		check_for_hierarchy_violation();
		internal_mutex.lock(); // 4
		update_hierarchy_value(); // 5
	}
	void unlock()
	{
		this_thread_hierarchy_value = previous_hierarchy_value; // 6
		internal_mutex.unlock();
	}
	bool try_lock()  //当互斥量上的锁被一个线程持有，它将返回false，而不是等待调用的线程，直到能够获取互斥量上的锁为止。
	{
		check_for_hierarchy_violation();
		if (!internal_mutex.try_lock()) // 7
			return false;
		update_hierarchy_value();
		return true;
	}
};
thread_local unsigned long
hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX); // 7

//3.7 使用层次锁来避免死锁
hierarchical_mutex high_level_mutex(10000); // 1 层级为10000 高级层级mutex
hierarchical_mutex low_level_mutex(5000); // 2
int do_low_level_stuff();
int low_level_func()
{
	std::lock_guard<hierarchical_mutex> lk(low_level_mutex); // 3
	return do_low_level_stuff();
}
void high_level_stuff(int some_param);
void high_level_func()
{
	std::lock_guard<hierarchical_mutex> lk(high_level_mutex); // 4
	high_level_stuff(low_level_func()); // 5
}
void thread_a() // 6 ok 先锁住层级高的锁 在锁住层级低的
{
	high_level_func();
}
hierarchical_mutex other_mutex(100); // 7
void do_other_stuff();
void other_stuff()
{
	high_level_func(); // 8
	do_other_stuff();
}
void thread_b() // 9 failed other_mutex层级低
{
	std::lock_guard<hierarchical_mutex> lk(other_mutex); // 10
	other_stuff();
}