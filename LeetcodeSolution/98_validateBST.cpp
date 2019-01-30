/**
* Definition for a binary tree node.
*/
#include<iostream>
#include<vector>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void inorderTraversal(TreeNode *root, vector<int> &inorder) {
	if (root == NULL)
		return;
	inorderTraversal(root->left,inorder);
	inorder.push_back(root->val);
	inorderTraversal(root->right, inorder);
}



bool isValidBST(TreeNode* root) {
	if (root == NULL)
		return false;
	vector<int> inorder;
	inorderTraversal(root, inorder);
	for (int i = 0; i < inorder.size()-1; i++)
		if (inorder[i] >= inorder[i + 1])
			return false;

	return true;
}

int main() {
	TreeNode *root = new TreeNode(2);
	root->left = new TreeNode(0);
	root->right = new TreeNode(3);
	cout << isValidBST(root);

}