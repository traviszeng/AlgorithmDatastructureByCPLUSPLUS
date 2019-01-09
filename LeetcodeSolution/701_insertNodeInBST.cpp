/**
* Definition for a binary tree node.
*/
#include<iostream>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* insertIntoBST(TreeNode* &root, int val) {

	if (root == NULL) {
		root = new TreeNode(val);
		return root;
	}
	if (val < root->val)
		insertIntoBST(root->left, val);
	if (val > root->val)
		insertIntoBST(root->right, val);

	return root;

}

int main() {
	TreeNode* node = new TreeNode(4);
	node->left = new TreeNode(2);
	node->right = new TreeNode(7);

	node->left->left = new TreeNode(1);
	node->left->right = new TreeNode(3);

	insertIntoBST(node, 5);

}