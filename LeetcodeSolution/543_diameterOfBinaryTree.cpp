#include<iostream>
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int treeDepth(TreeNode *root) {
	if (root == nullptr)
		return 0;
	int left = treeDepth(root->left);
	int right = treeDepth(root->right);
	return left > right ? left + 1 : right + 1;
}

int diameterOfBinaryTree(TreeNode* root) {
	//遍历所有节点，经过该节点最长的路径为左子树深度+右子树深度+1
	if (nullptr == root)
		return 0;
	int max = treeDepth(root->left) + treeDepth(root->right);
	//cout<<max<<endl;
	int left = 0;
	int right = 0;
	if (root->left) {
		left = diameterOfBinaryTree(root->left);
		max = max > left ? max : left;
	}
	if (root->right) {
		right = diameterOfBinaryTree(root->right);
		max = max > right ? max : right;
	}
	return max;
}