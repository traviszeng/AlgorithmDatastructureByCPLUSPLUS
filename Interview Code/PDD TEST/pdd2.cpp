#include<vector>
#include<iostream>
using namespace std;

/*
�и����б�ʾ����0-9���Ա�ʹ�õĴ�����������������AB����Щ������ɣ�
��֪A B�ĸ��Ե�λ������A��B�˻�����Сֵ
65% passed
*/
int main() {
	int a[10];
	for (int i = 0; i < 10; i++)
		cin >> a[i];

	int x, y;
	cin >> x >> y;

	//������λ��С�� ��λ��С�ľ�����С

	if (x > y) {
		int sum = 0;
		int endwith;
		for (int i = 0; i < 10; i++) {
			sum += a[i];
			if (sum >= y)
			{//������endwith���Է�����λ��С������
				endwith = i;
				break;
			}
		}
		sum = 0;
		for (int i = 0; i <= endwith; i++) {
			if (a[i] == 0)
				continue;
			while (a[i] != 0 && y != 0) {
				sum *= 10;
				sum += i;
				a[i]--;
				y--;
			}

		}
		int sum2 = 0;
		for (int i = endwith; i < 10; i++) {
			if (x == 0) break;
			if (a[i] == 0)
				continue;
			while (a[i] != 0 && x != 0) {
				sum2 *= 10;
				sum2 += i;
				a[i]--;
				x--;
			}
		}
		cout<<sum * sum2;
	}
	else {
		int sum = 0;
		int endwith;
		for (int i = 0; i < 10; i++) {
			sum += a[i];
			if (sum >= x) {
				//������endwith���Է�����λ��С������
				endwith = i;
				break;
			}
		}
		sum = 0;
		for (int i = 0; i <= endwith; i++) {
			if (a[i] == 0)
				continue;
			while (a[i] != 0 && x != 0) {
				sum *= 10;
				sum += i;
				a[i]--;
				x--;
			}

		}
		int sum2 = 0;
		for (int i = endwith; i < 10; i++) {
			if (y == 0) break;
			if (a[i] == 0)
				continue;
			while (a[i] != 0 && y != 0) {
				sum2 *= 10;
				sum2 += i;
				a[i]--;
				y--;
			}
		}
		cout<<sum * sum2;
	}
	return 0;
}