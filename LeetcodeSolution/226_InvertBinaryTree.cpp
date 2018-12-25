/**
Invert a binary tree.

Example:

Input:

4
/   \
2     7
/ \   / \
1   3 6   9
Output:

4
/   \
7     2
/ \   / \
9   6 3   1

*/

#include<iostream>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* invertTree(TreeNode* root) {
	if (root == NULL)
		return NULL;
	if (root->left == NULL&&root->right == NULL)
		return root;
	if (root->left != NULL&&root->right == NULL) {
		root->right = invertTree(root->left);
		root->left = NULL;
		return root;
	}
	if (root->right != NULL&&root->left == NULL) {
		root->left = invertTree(root->right);
		root->right = NULL;
		return root;
	}
	TreeNode* temp = invertTree(root->left);
	root->left = invertTree(root->right);
	root->right = temp;
	return root;
}