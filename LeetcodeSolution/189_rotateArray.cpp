#include<vector>
using namespace std;

void rotate(vector<int>& nums, int k) {
	/*
	//brutal-force TLE
	while(k--){
		int size = nums.size();
		for(int i = size-2;i>=0;i--){
			int temp = nums[i];
			nums[i] = nums[i+1];
			nums[i+1] = temp;
		}

	}*/
	/*
	int size = nums.size();
	if(k>size)
		k = k%size;
	for(int i =0;i<k;i++){
		int temp = *(nums.end()-1);
		nums.erase(nums.end()-1);
		nums.insert(nums.begin(),temp);
	}
	*/
	vector<int>::iterator iter = nums.begin();
	int size = nums.size();
	if (k > size)
		k = k % size;
	for (int i = 0; i < size - k; i++) {
		iter++;
	}
	nums.insert(nums.begin(), iter, iter + k);
	nums.erase(nums.begin() + size, nums.end());
}