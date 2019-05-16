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
		/**��׼�����ݵ��̵߳���notify_one()֪ͨ��������ʱ���������ݵ��̴߳�˯��״̬�����ѣ����»�ȡ�����������Ҷ������ٴμ�飬
	���������������£���wait()���ز�������������������������ʱ���߳̽��Ի�����������
	�������¿�ʼ�ȴ��������Ϊʲô�� std::unique_lock ����ʹ�� std::lock_guard �����ȴ���
	���̱߳����ڵȴ��ڼ��������������������֮��Ի������ٴ��������� std::lock_guard û
	����ô��*/
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
