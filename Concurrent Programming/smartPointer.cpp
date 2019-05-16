#include <iostream>
#include <memory>


class Child;
class Parent;

class Parent {
private:
	//std::shared_ptr<Child> ChildPtr;
	std::weak_ptr<Child> ChildPtr;
public:
	void setChild(std::shared_ptr<Child> child) {
		this->ChildPtr = child;
	}

	void doSomething() {
		//new shared_ptr
		if (this->ChildPtr.lock()) {

		}
	}

	~Parent() {
	}
};

class Child {
private:
	std::shared_ptr<Parent> ParentPtr;
public:
	void setPartent(std::shared_ptr<Parent> parent) {
		this->ParentPtr = parent;
	}
	void doSomething() {
		if (this->ParentPtr.use_count()) {

		}
	}
	~Child() {
	}
};

//智能指针的实现
template<typename T>
class SmartPointer {
private:
	T* _ptr;
	size_t* _count;
public:
	SmartPointer(T* ptr = nullptr) :
		_ptr(ptr) {
		if (_ptr) {
			_count = new size_t(1);
		}
		else {
			_count = new size_t(0);
		}
	}

	SmartPointer(const SmartPointer& ptr) {
		if (this != &ptr) {
			this->_ptr = ptr._ptr;
			this->_count = ptr._count;
			(*this->_count)++;
		}
	}

	SmartPointer& operator=(const SmartPointer& ptr) {
		if (this->_ptr == ptr._ptr) {
			return *this;
		}

		if (this->_ptr) { //减少左值操作数所指对象的引用计数
			(*this->_count)--;
			if (this->_count == 0) {
				delete this->_ptr;
				delete this->_count;
			}
		}

		this->_ptr = ptr._ptr;
		this->_count = ptr._count;
		(*this->_count)++;
		return *this;
	}

	T& operator*() {
		assert(this->_ptr == nullptr);
		return *(this->_ptr);

	}

	T* operator->() {
		assert(this->_ptr == nullptr);
		return this->_ptr;
	}

	~SmartPointer() {
		(*this->_count)--;
		if (*this->_count == 0) {
			delete this->_ptr;
			delete this->_count;
		}
	}

	size_t use_count() {
		return *this->_count;
	}
};


int main() {
	
	int a = 10;
	std::shared_ptr<int> ptra = std::make_shared<int>(a);
	std::shared_ptr<int> ptra2(ptra); //copy
	std::cout << ptra.use_count() << std::endl;

	int b = 20;
	int *pb = &a;
	//std::shared_ptr<int> ptrb = pb;  //error
	std::shared_ptr<int> ptrb = std::make_shared<int>(b);
	ptra2 = ptrb; //assign
	pb = ptrb.get(); //获取原始指针

	std::cout << ptra.use_count() << std::endl;
	std::cout << ptrb.use_count() << std::endl;


	std::unique_ptr<int> uptr(new int(10));  //绑定动态对象
		//std::unique_ptr<int> uptr2 = uptr;  //不能賦值
		//std::unique_ptr<int> uptr2(uptr);  //不能拷貝
	std::unique_ptr<int> uptr2 = std::move(uptr); //轉換所有權
	uptr2.release(); //释放所有权
	


	std::shared_ptr<int> sh_ptr = std::make_shared<int>(10);
	std::cout << sh_ptr.use_count() << std::endl;

	std::weak_ptr<int> wp(sh_ptr);
	std::cout << wp.use_count() << std::endl;

	if (!wp.expired()) { //expired本质上等价于use_count()==0
		std::shared_ptr<int> sh_ptr2 = wp.lock(); //get another shared_ptr 从观测资源变成可操作
		*sh_ptr = 100;
		std::cout << wp.use_count() << std::endl;
	}


	std::weak_ptr<Parent> wpp;
	std::weak_ptr<Child> wpc;
	{
		std::shared_ptr<Parent> p(new Parent);
		std::shared_ptr<Child> c(new Child);
		p->setChild(c);
		c->setPartent(p);
		wpp = p;
		wpc = c;
		std::cout << p.use_count() << std::endl; // 2
		std::cout << c.use_count() << std::endl; // 1
	}
	std::cout << wpp.use_count() << std::endl;  // 0
	std::cout << wpc.use_count() << std::endl;  // 0
	system("pause");
}//超過uptr的作用域，內存釋放
