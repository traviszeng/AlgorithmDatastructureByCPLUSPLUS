#include<iostream>
#include<thread>
#include<vector>

/*
2.2 ���̺߳������ݲ���
*/
void f(int i, std::string const& s);
void oops(int some_param) {
	char buffer[1024]; 
	sprintf(buffer, "%i", some_param);
	//std::thread t(f, some_param, buffer);  //�п��ܻ�������ֵbufferת��Ϊstring֮ǰ����
	std::thread t(f, some_param, std::string(buffer));  //��������ָ��
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
	//std::thread t(update_data_for_widget, w, data); //  thread���캯����֪����Ҫ�������ã�äĿ��data����һ�ݴ����߳��У�
													//���ݸ������Ĳ�����data�����ڲ����������ã��������ݱ��������
													//  �߳̽������ڲ����������ݻ������ݸ��½׶α����٣�dataδ������
	std::thread t(update_data_for_widget, w, std::ref(data)); //ʹ�� std::ref ������ת�������õ���ʽ
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
std::thread t(&X::do_lengthy_work, &my_x, num);//���߳̽�my_x.do_lengthy_work()��Ϊ�̺߳�����my_x�ĵ�ַ��Ϊָ������ṩ������



//2-3

void some_function();
void some_other_function();
std::thread t1(some_function); // 1
// std::thread t2 = t1; // ������� �̶߳���֮���ǲ��ܸ��Ƶģ�ֻ���ƶ�
std::thread t2 = std::move(t1); // 2
t1 = std::thread(some_other_function); // 3 ��ʽ����move
std::thread t3; // 4 
t3 = std::move(t2); // 5
//t1.terminate();
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

//2-4

//���а�std::accumulate
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
		(length + min_per_thread - 1) / min_per_thread; // 2 �÷�Χ��Ԫ�ص������������߳�(��)����С���������Ӷ�ȷ�������̵߳��������
	unsigned long const hardware_threads =
		std::thread::hardware_concurrency();
	/*�����������ֵ��Ӳ��֧���߳����У���С��ֵΪ�����̵߳������ۡ���Ϊ������Ƶ�����л�
�ή���̵߳����ܣ�������϶������������߳�������Ӳ��֧�ֵ��߳�����*/
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

//���̷ָ߳�һ���
std::thread::id master_thread;
void some_core_part_of_algorithm() {
	if (std::this_thread::get_id() == master_thread) {
		do_master_thread_work();
	}
	do_common_work();
}