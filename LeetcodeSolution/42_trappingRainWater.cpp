#include<vector>

using namespace std;
/**
��˫ָ����������߳���
��ָ��ÿ����ߵ����ֵ�Ƚϣ���ָ��ÿ�κ��ұߵ����ֵ�Ƚϣ�ֻҪ��ǰֵС���������ֵ���ڵ�ǰλ��������max-height��ˮ��
�����ǵ��ߵ���ˮ�أ���ߵĲ����ұߵ�ǽ���޸ߣ��ұߵĲ�����ߵ�ǽ���޸�
ˮ����ȡ�����������󣬺��ҵ������
*/
int trap(vector<int>& height) {
	int result = 0;
	int left = 0;
	int right = height.size()-1;
	int leftMax = 0, rightMax = 0;
	while (left <= right) {
		if (height[left] <= height[right]) {
			if (leftMax < height[left]) {
				leftMax = height[left];
			}
			else {
				result += leftMax - height[left];
			}
			left++;
		}

		else {
			if (rightMax <= height[right]) {
				rightMax = height[right];
			}
			else {
				result += rightMax - height[right];
			}
			right--;
		}
	}
	return result;
}