#include<stack>
template<typename T>
class CQueue {
public:
	CQueue(void);
	~CQueue(void);

	void appendTail(const T& node);
	T deleteHead();


private:
	stack<T> stack1;
	stack<T> stack2;
};

template<typename T>
CQueue::CQueue(void) {

}

template<typename T>
CQueue::~CQueue(void) {

}

/**
往队列尾部添加元素
*/
template<typename T>
void CQueue::appendTail(const T& node) {
	if (stack1 == nullptr)
		stack1 = new stack<T>();
	if (stack2 == nullptr)
		stack2 = new stack<T>();
	stack1.push(node);
}


/**
删除队列的头元素，并将其返回
*/
template<typename T>
T CQueue::deleteHead() {
	if (stack2.size() <= 0)
	{
		while (stack1.size()>0)
		{
			T& data = stack1.top();
			stack1.pop();
			stack2.push(data);
		}
	}

	if (stack2.size() == 0)
		throw new exception("queue is empty");

	T head = stack2.top();
	stack2.pop();

	return head;
}