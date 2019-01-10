/**
* Definition for a binary tree node.*/
#include<iostream>

using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
void traversal(TreeNode *root, int key, TreeNode *&keyNode);
void findSmallestNode(TreeNode *root, TreeNode *&smallestNode);

TreeNode* deleteNode(TreeNode* root, int key) {
	if (root == NULL)
		return root;
	if (key < root->val) {
		deleteNode(root->left, key);
	}
	else if (key > root->val) {
		deleteNode(root->right, key);
	}
	else if (root->left != NULL && root->right != NULL) {
		TreeNode *temp = root->right;
		while (temp->left != NULL)
			temp = temp->left;

		root->val = temp->val;
		deleteNode(root->right, root->val);
	}

	else {
		TreeNode *temp = root;

		if (root->left == NULL)
			root = root->right;
		else
			root = root->left;
		delete temp;

	}
	return root;

}



void traversal(TreeNode *root, int key, TreeNode *&keyNode) {
	if (root == NULL)
		return;
	if (root->val == key)
	{
		keyNode = root;
	}
	else if (key < root->val) {
		traversal(root->left, key, keyNode);
	}
	else {
		traversal(root->right, key, keyNode);
	}

}


int main() {
	TreeNode *root = new TreeNode(5);
	root->left = new TreeNode(3);
	root->right = new TreeNode(6);
	root->left->left = new TreeNode(2);
	root->left->right = new TreeNode(4);
	root->right->right = new TreeNode(7);


	deleteNode(root, 3);
}