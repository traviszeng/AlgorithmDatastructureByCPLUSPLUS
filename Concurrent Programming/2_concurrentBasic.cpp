#include<iostream>
#include<thread>
#include<vector>

/*
2.2 向线程函数传递参数
*/
void f(int i, std::string const& s);
void oops(int some_param) {
	char buffer[1024]; 
	sprintf(buffer, "%i", some_param);
	//std::thread t(f, some_param, buffer);  //有可能会在字面值buffer转化为string之前崩溃
	std::thread t(f, some_param, std::string(buffer));  //避免悬垂指针
	t.detach();
}


typedef int widget_id ;
typedef std::string widget_data;
void update_data_for_widget(widget_id w, widget_data& data); // 1
void display_status();
void process_widget_data(widget_data& data);
void oops_again(widget_id w)
{
	widget_data data;
	//std::thread t(update_data_for_widget, w, data); //  thread构造函数不知道需要传入引用，盲目将data拷贝一份传到线程中，
													//传递给函数的参数是data变量内部拷贝的引用，而非数据本身的引用
													//  线程结束，内部拷贝的数据会在数据更新阶段被销毁，data未被更新
	std::thread t(update_data_for_widget, w, std::ref(data)); //使用 std::ref 将参数转换成引用的形式
	display_status();
	t.join();
	process_widget_data(data); // 3
}


class X
{
public:
	void do_lengthy_work(int);
};
X my_x;
int num(0);
std::thread t(&X::do_lengthy_work, &my_x, num);//新线程将my_x.do_lengthy_work()作为线程函数；my_x的地址作为指针对象提供给函数



//2-3

void some_function();
void some_other_function();
std::thread t1(some_function); // 1
// std::thread t2 = t1; // 编译错误 线程对象之间是不能复制的，只能移动
std::thread t2 = std::move(t1); // 2
t1 = std::thread(some_other_function); // 3 隐式调用move
std::thread t3; // 4 
t3 = std::move(t2); // 5
//t1.terminate();
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

//2-4

//并行版std::accumulate
template<typename Iterator, typename T>
struct accumulate_block
{
	void operator()(Iterator first, Iterator last, T& result)
	{
		result = std::accumulate(first, last, result);
	}
};
template<typename Iterator, typename T>
T parallel_accumulate(Iterator first, Iterator last, T init)
{
	unsigned long const length = std::distance(first, last);
	if (!length) // 1
		return init;
	unsigned long const min_per_thread = 25;
	unsigned long const max_threads =
		(length + min_per_thread - 1) / min_per_thread; // 2 用范围内元素的总数量除以线程(块)中最小任务数，从而确定启动线程的最大数量
	unsigned long const hardware_threads =
		std::thread::hardware_concurrency();
	/*计算量的最大值和硬件支持线程数中，较小的值为启动线程的数量③。因为上下文频繁的切换
会降低线程的性能，所以你肯定不想启动的线程数多于硬件支持的线程数量*/
	unsigned long const num_threads = // 3
		std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);
	unsigned long const block_size = length / num_threads; // 4
	std::vector<T> results(num_threads);
	std::vector<std::thread> threads(num_threads - 1); // 5
	Iterator block_start = first;
	for (unsigned long i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size); // 6
		threads[i] = std::thread( // 7
			accumulate_block<Iterator, T>(),
			block_start, block_end, std::ref(results[i]));
		block_start = block_end; // 8
	}
	accumulate_block<Iterator, T>()(
		block_start, last, results[num_threads - 1]); // 9
	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join)); // 10
	return std::accumulate(results.begin(), results.end(), init); // 11
}

//用线程分割一项工作
std::thread::id master_thread;
void some_core_part_of_algorithm() {
	if (std::this_thread::get_id() == master_thread) {
		do_master_thread_work();
	}
	do_common_work();
}