#include<iostream>
using namespace std;
/**
* Definition for a binary tree node.*/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int sumOfLeftLeaves(TreeNode* root) {
	int sum = 0;
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 0;
	if (root->right != NULL)
		sum += sumOfLeftLeaves(root->right);
	if (root->left != NULL) {
		sum += sumOfLeftLeaves(root->left);
	}
	if (root->left != NULL && root->left->right == NULL && root->left->left == NULL)
		sum += root->left->val;
	return sum;
}
