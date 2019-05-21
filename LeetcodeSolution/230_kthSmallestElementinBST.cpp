#include<vector>
using namespace std;

struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
	TreeNode(int x) :val(x) {}
};

void traversal(TreeNode* root, vector<int>& num) {
	if (root == nullptr)
		return;
	traversal(root->left, num);
	num.push_back(root->val);
	traversal(root->right, num);
}

int kthSmallest(TreeNode* root, int k) {
	vector<int> num;
	if (root == nullptr)
		return 0;
	traversal(root, num);
	return num[k-1];

}
