#pragma once
#ifndef THREADSAFE_QUEUE_WITHSHAREDPTR
#define THREADSAFE_QUEUE_WITHSHAREDPTR
/**
	当不止一个线程等待对队列进行推送操作是，只会有一个
	线程，因得到data_cond.notify_one()，而继续工作着。但是，如果这个工作线程在
	wait_and_pop()中抛出一个异常，例如：构造新的 std::shared_ptr<> 对象④时抛出异常，那
	么其他线程则会永世长眠。当这种情况是不可接受时，这里的调用就需要改成
	data_cond.notify_all()，这个函数将唤醒所有的工作线程，不过，当大多线程发现队列依旧是
	空时，又会耗费很多资源让线程重新进入睡眠状态。第二种替代方案是，当有异常抛出的时
	候，让wait_and_pop()函数调用notify_one()，从而让个另一个线程可以去尝试索引存储的
	值。第三种替代方案就是，将 std::shared_ptr<> 的初始化过程移到push()中，并且存
	储 std::shared_ptr<> 实例，而非直接使用数据的值。将 std::shared_ptr<> 拷贝到内
	部 std::queue<> 中，就不会抛出异常了，这样wait_and_pop()又是安全的了。
*/
#include<mutex>
#include<memory>
#include<queue>
template<typename T>
class threadsafe_queue
{
private:
	mutable std::mutex mut;
	std::queue<std::shared_ptr<T> > data_queue;
	std::condition_variable data_cond;
public:
	threadsafe_queue()
	{}
	void wait_and_pop(T& value)
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		value = std::move(*data_queue.front()); // 1
		data_queue.pop();
	}
	bool try_pop(T& value)
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return false;
		value = std::move(*data_queue.front()); // 2
		data_queue.pop();
		return true;
	}
	std::shared_ptr<T> wait_and_pop()
	{
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		std::shared_ptr<T> res = data_queue.front(); // 3
		data_queue.pop();
		return res;
	}
	std::shared_ptr<T> try_pop() {
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return std::shared_ptr<T>();
		std::shared_ptr<T> res = data_queue.front(); // 4
		data_queue.pop();
		return res;
	}
	void push(T new_value)
	{
		/**新的实例分配结束时，不会被锁在push()⑤当中(而在清
		单6.2中，只能在pop()持有锁时完成)。因为内存分配操作的需要在性能上付出很高的代价(性
		能较低)，所以使用 std::shared_ptr<> 的方式对队列的性能有很大的提升，其减少了互斥量持
		有的时间，允许其他线程在分配内存的同时，对队列进行其他的操作。*/
		std::shared_ptr<T> data(
			std::make_shared<T>(std::move(new_value))); // 5
		std::lock_guard<std::mutex> lk(mut);
		data_queue.push(data);
		data_cond.notify_one();
	}
	bool empty() const
	{
		std::lock_guard<std::mutex> lk(mut);
		return data_queue.empty();
	}
};

#endif // !THREADSAFE_QUEUE_WITHSHAREDPTR

