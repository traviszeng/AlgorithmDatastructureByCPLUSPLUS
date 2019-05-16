#pragma once
#ifndef THREADSAFE_QUEUE
#define THREADSAFE_QUEUE
#include<mutex>
#include<queue>

template<typename T>
class threadsafe_queue
{
private:
	mutable std::mutex mut;
	std::queue<T> data_queue;
	std::condition_variable data_cond;
public:
	threadsafe_queue() {}

	void push(T new_value) {
		std::lock_guard<std::mutex> lock(mut);
		data_queue.push(std::move(new_value));
		data_cond.notify_one();
	}


	void wait_and_pop(T& value) {
		/**当准备数据的线程调用notify_one()通知条件变量时，处理数据的线程从睡眠状态中苏醒，重新获取互斥锁，并且对条件再次检查，
	在条件满足的情况下，从wait()返回并继续持有锁。当条件不满足时，线程将对互斥量解锁，
	并且重新开始等待。这就是为什么用 std::unique_lock 而不使用 std::lock_guard ——等待中
	的线程必须在等待期间解锁互斥量，并在这这之后对互斥量再次上锁，而 std::lock_guard 没
	有这么灵活。*/
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		value = std::move(data_queue.front());
		data_queue.pop();
	}

	std::shared_ptr<T> wait_and_pop() {
		std::unique_lock<std::mutex> lk(mut);
		data_cond.wait(lk, [this] {return !data_queue.empty(); });
		shared_ptr<T> ptr = std::make_shared<T>(data_queue.front());
		data_queue.pop();
		return ptr;
	}

	bool try_pop(T& value)
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return false;
		value = std::move(data_queue.front());
		data_queue.pop();
		return true;
	}
	std::shared_ptr<T> try_pop()
	{
		std::lock_guard<std::mutex> lk(mut);
		if (data_queue.empty())
			return std::shared_ptr<T>(); // 5
		std::shared_ptr<T> res(
			std::make_shared<T>(std::move(data_queue.front())));
		data_queue.pop();
		return res;
	}
	bool empty() const
	{
		std::lock_guard<std::mutex> lk(mut);
		return data_queue.empty();
	}

};
#endif // !THREADSAFE_QUEUE
