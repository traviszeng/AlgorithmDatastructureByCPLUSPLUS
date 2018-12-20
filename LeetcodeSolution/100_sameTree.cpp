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


bool isSameTree(TreeNode* p, TreeNode* q) {

	if (p == NULL && q != NULL)
		return false;
	if (q == NULL && p != NULL)
		return false;
	if (q == NULL && q == NULL)
		return true;

	if (p->val != q->val)
		return false;



	if (!isSameTree(p->left, q->left) || !isSameTree(p->right, q->right))
		return false;
}