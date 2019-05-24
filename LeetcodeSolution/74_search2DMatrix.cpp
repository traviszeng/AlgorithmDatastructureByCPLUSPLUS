#include<vector>
using namespace std;


bool searchMatrix(vector<vector<int>>& matrix, int target) {
	if (matrix.empty() || matrix[0].empty())
	{
		return false;
	}
	int row = 0;
	if (matrix[0][0] > target)
		return false;
	for (int i = 1; i < matrix.size(); i++)
	{
		if (matrix[i][0] <= target)
			row = i;
		else
			break;
	}
	bool flag = false;
	for (int i = 0; i < matrix[row].size(); i++)
	{
		if (matrix[row][i] == target)
			flag = true;
	}

	return flag;
}