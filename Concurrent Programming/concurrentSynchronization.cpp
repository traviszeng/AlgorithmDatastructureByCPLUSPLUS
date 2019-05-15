#include<mutex>
#include<queue>

bool flag;
std::mutex m;
void wait_for_flag()
{
	std::unique_lock<std::mutex> lk(m);
	while (!flag)
	{
		lk.unlock(); // 1 ����������
		std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 2 ����100ms
		lk.lock(); // 3 ����������
	}
}

/**������ǰ�ڣ������Ի��������н����٣����������߽������ٶԻ�����������
��������������߳̾��л����ȡ�������ñ�ʶ��*/


//4.1  ʹ�� std::condition_variable �������ݵȴ�
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

//4.5 �̰߳�ȫ�Ķ���
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
template<typename T>
class threadsafe_queue
{
private:
	mutable std::mutex mut; // 1 �����������ǿɱ��
	/*�����ס��������һ���ɱ��������ô�������������ͻ���Ϊ�ɱ�Ģ٣�֮������
������empty()�Ϳ������캯����������*/
	std::queue<T> data_queue;
	std::condition_variable data_cond;
public:
	threadsafe_queue()
	{}
	threadsafe_queue(threadsafe_queue const& other)
	{
		
		std::lock_guard<std::mutex> lk(other.mut); //��֤��ʱother��ס
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
		std::shared_ptr<T> res(std::make_shared<T>(data_queue.front())); //make_shared �ڶ�̬�ڴ��з���һ�����󲢳�ʼ����������ָ��˶����shared_ptr
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

//4.6 ʹ�� std::future ���첽�����л�ȡ����ֵ
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
auto f1 = std::async(&X::foo, &x, 42, "hello"); // ����p->foo(42, "hello")��p��ָ��x��ָ��
auto f2 = std::async(&X::bar, x, "goodbye"); // ����tmpx.bar("goodbye")�� tmpx��x�Ŀ�������
struct Y
{
	double operator()(double);
};

void maintest() {
	Y y;
	auto f3 = std::async(Y(), 3.141); // ����tmpy(3.141)��tmpyͨ��Y���ƶ����캯���õ�
	auto f4 = std::async(std::ref(y), 2.718); // ����y(2.718)
	X baz(X&);
	std::async(baz, std::ref(x)); // ����baz(x)
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
auto f5 = std::async(move_only()); // ����tmp()��tmp��ͨ��std::move(move_only())����õ�