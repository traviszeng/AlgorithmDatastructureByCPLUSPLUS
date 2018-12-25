/**
 Definition for a binary tree node.*/
/**
Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.

Note: A leaf is a node with no children.

Example:

Given the below binary tree and sum = 22,

5
/ \
4   8
/   / \
11  13  4
/  \      \
7    2      1

*/
#include<iostream>
using namespace std;
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };



bool hasPathSum(TreeNode* root, int sum) {
	if (root == NULL)
		return false;
	if (root->left == NULL&&root->right == NULL&&root->val != sum)
		return false;
	if (root->val == sum&&root->left == NULL&&root->right == NULL)
		return true;

	if (root->left == NULL&&root->right != NULL&&sum != root->val)
		return hasPathSum(root->right, sum - root->val);
	if (root->left != NULL&&root->right == NULL&&sum != root->val)
		return hasPathSum(root->left, sum - root->val);


	return hasPathSum(root->left, sum - root->val) || hasPathSum(root->right, sum - root->val);

}