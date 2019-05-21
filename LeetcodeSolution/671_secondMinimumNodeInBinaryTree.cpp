#include<set>
#include<vector>
#include<algorithm>
using namespace std;

struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
	TreeNode(int x) :val(x) {}
};

void traversal(TreeNode* root, set<int>& num) {
	if (root == nullptr)
		return;
	traversal(root->left, num);
	num.insert(root->val);
	traversal(root->right, num);
}

int findSecondMinimumValue(TreeNode* root) {
	set<int> num;
	traversal(root, num);
	vector<int> number;
	number.assign(num.begin(), num.end());
	/*for(int i = 0;i<number.size();i++)
		cout<<number[i]<<endl;*/
	if (number.size() <= 1) return -1;
	return number[1];
}