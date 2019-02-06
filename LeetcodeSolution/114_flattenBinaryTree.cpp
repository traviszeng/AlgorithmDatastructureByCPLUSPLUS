/**
* Definition for a binary tree node.
*
*/
#include<iostream>
#include<queue>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


TreeNode *pt = NULL;
void flatten(TreeNode* root) {
	if (!root)
		return;
	else {
		TreeNode *tp1 = root->left, *tp2 = root->right;
		if (pt == NULL) {
			pt = root;
			pt->left = NULL;
			pt->right = NULL;
			root = pt;
		}
		else {
			pt->right = root;
			pt = pt->right;
			pt->left = NULL;
			pt->right = NULL;
		}

		flatten(tp1);
		flatten(tp2);
	}