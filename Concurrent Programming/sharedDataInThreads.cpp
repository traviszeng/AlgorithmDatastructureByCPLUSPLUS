#include<deque>
#include<list>
#include<mutex>
#include<algorithm>
#include <exception>
#include <memory>
#include <mutex>
#include <stack>

//3.1

std::list<int> some_list; // 1 ��ȫ�ֵĻ�����some_mutex����
std::mutex some_mutex; // 2
void add_to_list(int new_value)
{
	std::lock_guard<std::mutex> guard(some_mutex); // 3ʹ��lock_guard�����ֶ�дmutex.unlock() ����guardʱ���Զ�����unlock() ��ֹ�쳣����ʱû��unlock
	some_list.push_back(new_value);
}
bool list_contains(int value_to_find)
{
	std::lock_guard<std::mutex> guard(some_mutex); // 4
	return std::find(some_list.begin(), some_list.end(), value_to_find) != some_list.end()
		;
}

//add_to_list��list_contains���⣬�����ݵķ����ǻ���ģ�list_contains()�����ܿ������ڱ�add_to_list()�޸ĵ��б�
/**������һ����Ա�������ص��Ǳ������ݵ�ָ�������ʱ�����ƻ������ݵı�����
���з���������ָ������ÿ��Է���(�������޸�)�����������ݣ������ᱻ���������ơ�*/

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
		func(data); // 1 ���ݡ����������ݸ��û�����
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
	x.process_data(malicious_function); // 2 ����һ�����⺯��
	unprotected->do_something(); // 3 ���ޱ���������·��ʱ�������
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
	threadsafe_stack& operator=(const threadsafe_stack&) = delete; // 1 ��ֵ������ɾ��
	void push(T new_value);
	std::shared_ptr<T> pop(); //shared_ptr�����ܱ����ڴ�й¶(��Ϊ��������ָ������ʱ������Ҳ�ᱻ����)�����ұ�׼���ܹ���ȫ�����ڴ���䷽����Ҳ�Ͳ���Ҫnew��delete����
	void pop(T& value); //pop��ʱ��ʹ��һ���ֲ�����ȥ�洢����ֵ��������һ��std::shared_ptr<>����
	bool empty() const;
};*/

//3.5 �̰߳�ȫ��ջ����ʵ��

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
	mutable std::mutex m; //��Щʱ��������Ҫ��const�ĺ��������޸�һЩ����״̬�޹ص����ݳ�Ա����ô������ݳ�Ա��Ӧ�ñ�mutalbe������
public:
	threadsafe_stack()
		: data(std::stack<int>()) {}
	threadsafe_stack(const threadsafe_stack& other)
	{
		std::lock_guard<std::mutex> lock(other.m);
		data = other.data; // 1 �ڹ��캯�����е�ִ�п���
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
		if (data.empty()) throw empty_stack(); // �ڵ���popǰ�����ջ�Ƿ�Ϊ��
		std::shared_ptr<T> const res(std::make_shared<T>(data.top())); // ���޸Ķ�ջǰ�����������ֵ
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

//Ԥ������ �����������֮���໥�ȴ���
//����������һ�㽨�飬����������������������ͬ��˳������
/*C++��׼���а취���������⣬ std::lock ��������һ������ס���(��������)��
������������û�и�����(��������)*/

//3.6

// �����std::lock()��Ҫ����<mutex>ͷ�ļ�
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
		std::lock(lhs.m, rhs.m); // 1 Ҫô��������ס��Ҫôһ��������
		/**�ṩ std::adopt_lock �������˱�ʾ std::lock_guard �����Ѿ������⣬����ʾ�ֳ�
		���������ǳ��Դ����µ�����*/
		std::lock_guard<std::mutex> lock_a(lhs.m, std::adopt_lock); // 2
		std::lock_guard<std::mutex> lock_b(rhs.m, std::adopt_lock); // 3
		swap(lhs.some_detail, rhs.some_detail);
	}

};


//3.8 �������ʵ��
/**��������һ���û��������ͣ����������� std::lock_guard<> ģ���У���Ϊ����
ʵ����������Ա����Ϊ�����㻥����������lock(), unlock() �� try_lock()*/
class hierarchical_mutex
{
	std::mutex internal_mutex;
	unsigned long const hierarchy_value;
	unsigned long previous_hierarchy_value;
	/**��Ϊ����������thread_local������ÿ���̶߳����俽�������������߳��б���״̬��ȫ������
������һ���߳̽��ж�ȡʱ��������״̬Ҳ��ȫ����*/
	static thread_local unsigned long this_thread_hierarchy_value; // 1 ��ʹ����thread_local��ֵ������ǰ�̵߳Ĳ㼶ֵ��this_thread_hierarchy_value
																   //������ʼ��Ϊ���ֵ�࣬������������̶߳��ܱ���ס
	void check_for_hierarchy_violation()
	{
		if (this_thread_hierarchy_value <= hierarchy_value) // 2
		{
			throw std::logic_error("mutex hierarchy violated");
		}
	}
	void update_hierarchy_value() //���²㼶ֵ
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
	bool try_lock()  //���������ϵ�����һ���̳߳��У���������false�������ǵȴ����õ��̣߳�ֱ���ܹ���ȡ�������ϵ���Ϊֹ��
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

//3.7 ʹ�ò��������������
hierarchical_mutex high_level_mutex(10000); // 1 �㼶Ϊ10000 �߼��㼶mutex
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
void thread_a() // 6 ok ����ס�㼶�ߵ��� ����ס�㼶�͵�
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
void thread_b() // 9 failed other_mutex�㼶��
{
	std::lock_guard<hierarchical_mutex> lk(other_mutex); // 10
	other_stuff();
}