#include<iostream>
#include<thread>

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