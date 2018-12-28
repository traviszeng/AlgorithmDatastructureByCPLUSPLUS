#include<iostream>
#include<vector>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


vector<int> postorderTraversal(TreeNode* root) {
	vector<int> result;
	if (root == NULL)
		return result;
	posttraversal(result, root);
	return result;
}


void posttraversal(vector<int> &result, TreeNode* root) {
	if (root == NULL)
		return;

	posttraversal(result, root->left);
	posttraversal(result, root->right);
	result.push_back(root->val);
}

vector<int> preorderTraversal(TreeNode* root) {
	vector<int> result;
	if (root == NULL)
		return result;
	pretraversal(result, root);
	return result;
}

void pretraversal(vector<int> &result, TreeNode* root) {
	if (root == NULL)
		return;
	result.push_back(root->val);
	//result.push_back(traversal(result,root->left));
	//result.push_back(traversal(result,root->right));
	pretraversal(result, root->left);
	pretraversal(result, root->right);
}