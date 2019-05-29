#include<vector>
using namespace std;

vector<int> twoSum(vector<int>& numbers, int target) {
	int front = 0;
	int end = numbers.size() - 1;
	
	if (numbers.size() == 2) {
		vector<int> result{ 1, 2 };
		return result;
	}
	vector<int> result;
	
	while (front < end) {
		if (numbers[front] + numbers[end] == target)
		{
			result.push_back(front + 1);
			result.push_back(end + 1);
			break;
		}
		if (target - numbers[front] > numbers[end])
			front++;
		if (target - numbers[end] < numbers[front])
			end--;
	}
	return result;
}