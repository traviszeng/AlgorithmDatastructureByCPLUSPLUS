#include<vector>
#include<iostream>
#include<iomanip>
#include<string>
using namespace std;

/*
��һ��������ɫ������S����������ΪL
D��ʾ���ܽ��ܵ�ɫ��������ȡ��ֻ���ӵĲ�ֵ�ľ���ֵС�ڵ���d������Ա�����Ϊһ˫����
������Ա�����Ϊһ˫���ӵĸ���

����С�������λ

sample��
{31, 18, 19, 1, 25}
10

sample output:
0.400000

*/
int main() {
	
	vector<int> socks;
	char temp = 'a';
	int sum = 0;
	while (temp != '\n') {
		temp = cin.get();
		if (temp >= '0' &&temp <= '9') {
			sum *= 10;
			sum += temp - '0';
		}
		else {
			if (temp == ','||temp=='}')
			{
				socks.push_back(sum);
				sum = 0;
			}
			continue;
		}
	}


	int d;
	cin >> d;
	//int temp = 0;
	/*for (int i = 1; i < a.length() - 1; i++) {
		if (a[i] == ',')
		{
			socks.push_back(temp);
			temp = 0;
		}
		else {
			temp *= 10;
			temp += a[i] - '0';
		}
	}*/

	int count = 0;
	for (int i = 0; i < socks.size(); i++) {
	
		for (int j = i + 1; j < socks.size(); j++) {
			if (abs(socks[i] - socks[j]) <= d)
				count++;
		}
	}

	int num = socks.size();
	num = num * (num - 1) / 2;
	printf("%.6f",(float)count / num);
	

	//cout << percentage<<endl;
	system("pause");
	return 0;
}