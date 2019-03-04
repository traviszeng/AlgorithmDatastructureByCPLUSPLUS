#include<vector>
#include<iostream>

using namespace std;


vector<int> halfSearch(vector<int> &nums, int target, int start, int end);

vector<int> searchRange(vector<int>& nums, int target) {
	vector<int> result(2, -1);
	if (nums.size() <= 0)
		return result;
	return halfSearch(nums, target, 0, nums.size());
}


vector<int> halfSearch(vector<int> &nums, int target, int start, int end) {
	int half = (start + end) / 2;
	if (start >= end && nums[half]!=target)
	{
		vector<int> result(2, -1);
		return result;

	}
	if (start >= end && nums[half] == target)
	{
		vector<int> result(2, half);
		return result;
	}

	if (nums[half] == target)
	{
		int indice = half;
		vector<int> result;
		while ( indice >= 0 && nums[indice] == target )
			indice--;
		result.push_back(indice + 1);
		indice = half;
		while (indice <= nums.size()-1 && nums[indice] == target )
			indice++;

		result.push_back(indice - 1);
		return result;

	}
	else if (nums[half]>target) {
		return halfSearch(nums, target, start, half-1);

	}
	else
		return halfSearch(nums, target, half+1, end);

}


vector<int> searchRange(vector<int>& nums, int target) {
	int low = 0, hi = nums.size() - 1;
	int lower = -1;
	while (low <= hi) {
		int mid = low + (hi - low) / 2;
		if (nums[mid] == target) {
			lower = mid;
			hi = mid - 1;
		}
		else if (nums[mid]>target) {
			hi = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	vector<int> ans;
	ans.push_back(lower);
	int higher = -1;
	low = 0;
	hi = nums.size() - 1;
	while (low <= hi) {
		int mid = low + (hi - low) / 2;
		if (nums[mid] == target) {
			higher = mid;
			low = mid + 1;
		}
		else if (nums[mid]>target) {
			hi = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	ans.push_back(higher);
	return ans;
}


int main() {
	vector<int> a(1, 2);
	a.push_back(3);
	searchRange(a, 2);
}