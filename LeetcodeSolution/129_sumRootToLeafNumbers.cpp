/**
* Definition for a binary tree node.*/
#include<iostream>
#include<queue>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int sumTemp(TreeNode *root, int temp);
int result = 0;
int sumNumbers(TreeNode* root) {
	if (root == NULL)
		return;
	sumTemp(root, 0);
	return result;
}

int sumTemp(TreeNode *root, int temp) {
	if (root != NULL) {
		temp =temp*10+ root->val;
		if (root->left == NULL&&root->right == NULL) result += temp;
		sumTemp(root->left, temp);
		sumTemp(root->right, temp);
	}
}