#include<vector>
using namespace std;

int maxArea(vector<int>& height) {
	int start = 0;
	int end = height.size()-1;
	int max = 0;
	while (start <= end) {
		if (height[start] >= height[end]) {
			int temp = (end - start)*height[end];
			if (max < temp)
				max = temp;
			end--;
		}
		else {
			int temp = (end - start)*height[start];
			if (max < temp)
				max = temp;
			start++;
		}
	}
	return max;
}