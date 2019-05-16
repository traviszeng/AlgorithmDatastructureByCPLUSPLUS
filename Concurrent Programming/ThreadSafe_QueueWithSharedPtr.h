#pragma once
#ifndef THREADSAFE_QUEUE_WITHSHAREDPTR
#define THREADSAFE_QUEUE_WITHSHAREDPTR
/**
	����ֹһ���̵߳ȴ��Զ��н������Ͳ����ǣ�ֻ����һ��
	�̣߳���õ�data_cond.notify_one()�������������š����ǣ������������߳���
	wait_and_pop()���׳�һ���쳣�����磺�����µ� std::shared_ptr<> �����ʱ�׳��쳣����
	ô�����߳�����������ߡ�����������ǲ��ɽ���ʱ������ĵ��þ���Ҫ�ĳ�
	data_cond.notify_all()������������������еĹ����̣߳�������������̷߳��ֶ���������
	��ʱ���ֻ�ķѺܶ���Դ���߳����½���˯��״̬���ڶ�����������ǣ������쳣�׳���ʱ
	����wait_and_pop()��������notify_one()���Ӷ��ø���һ���߳̿���ȥ���������洢��
	ֵ������������������ǣ��� std::shared_ptr<> �ĳ�ʼ�������Ƶ�push()�У����Ҵ�
	�� std::shared_ptr<> ʵ��������ֱ��ʹ�����ݵ�ֵ���� std::shared_ptr<> ��������
	�� std::queue<> �У��Ͳ����׳��쳣�ˣ�����wait_and_pop()���ǰ�ȫ���ˡ�
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
		/**�µ�ʵ���������ʱ�����ᱻ����push()�ݵ���(������
		��6.2�У�ֻ����pop()������ʱ���)����Ϊ�ڴ�����������Ҫ�������ϸ����ܸߵĴ���(��
		�ܽϵ�)������ʹ�� std::shared_ptr<> �ķ�ʽ�Զ��е������кܴ��������������˻�������
		�е�ʱ�䣬���������߳��ڷ����ڴ��ͬʱ���Զ��н��������Ĳ�����*/
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

