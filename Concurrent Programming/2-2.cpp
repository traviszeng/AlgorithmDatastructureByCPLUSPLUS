#include<iostream>
#include<thread>

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