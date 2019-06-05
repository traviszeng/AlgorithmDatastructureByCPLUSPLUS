#include<vector>
using namespace std;
bool canPartition(vector<int>& nums) {
	int sum = 0;
	for (int i = 0; i < nums.size(); i++)
		sum += nums[i];
	if (sum % 2 == 1)
		return false;
	vector<vector<bool>> canForm(nums.size() + 1, vector<bool>(sum / 2 + 1, false));
	for (int i = 0; i < nums.size() + 1; i++) {
		canForm[i][0] = true;
	}
	for (int i = 1; i < nums.size() + 1; i++) {
		for (int j = nums[i]; j < sum / 2 + 1; j++) {

			if (j < nums[i - 1]) {
				canForm[i][j] = canForm[i - 1][j];

			}
			else {
				canForm[i][j] = canForm[i - 1][j] || canForm[i - 1][j - nums[i - 1]];

			}
		}
	}
	return canForm[nums.size()][sum / 2];

}