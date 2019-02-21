#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

/**
* Definition for a binary tree node.
* 
*/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};


void traverse(TreeNode *root,vector<int> &traversal) {
	if (root == NULL)
		return;
	traverse(root->left, traversal);
	traversal.push_back(root->val);
	
	traverse(root->right,traversal);
}

TreeNode* increasingBST(TreeNode* root) {
	vector<int> traversal;
	traverse(root, traversal);
	sort(traversal.begin(), traversal.end());
	TreeNode *newRoot = new TreeNode(traversal[0]);
	TreeNode *currentNode = newRoot;
	for (int i = 1; i < traversal.size(); i++) {
		currentNode->right = new TreeNode(traversal[i]);
		currentNode = currentNode->right;
	}
	
	return newRoot;

}