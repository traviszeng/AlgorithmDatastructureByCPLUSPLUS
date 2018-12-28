#include<iostream>
#include<string>

using namespace std;
/**
* Definition for a binary tree node.*/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


string tree2str(TreeNode *root) {	
	if (root == NULL)
		return "";
	if (root->left == NULL && root->right == NULL)
		return to_string(root->val)+"";
	if (root->right == NULL)
		return to_string(root->val) + "(" + tree2str(root->left) + ")";
	
	return to_string(root->val) + "(" + tree2str(root->left) + ")" + "(" + tree2str(root->right) + ")";
}

int main() {
	TreeNode *root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->right = new TreeNode(4);
	cout << tree2str(root) << endl;
	system("pause");

	

}