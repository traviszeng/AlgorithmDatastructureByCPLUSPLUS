#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
};

void traversalGetPath(TreeNode *root, string currentPath, vector<string> &result) {
	currentPath += to_string(root->val);
	if (root->left == NULL && root->right == NULL)
		result.push_back(currentPath);
	currentPath += "->";
	if (root->left != NULL)
		traversalGetPath(root->left, currentPath, result);
	if (root->right != NULL)
		traversalGetPath(root->right, currentPath, result);

}

vector<string> binaryTreePaths(TreeNode* root) {


	vector<string> result;
	if (root == NULL)
		return result;
	string currentPath = "";
	traversalGetPath(root, currentPath, result);
	return result;

}