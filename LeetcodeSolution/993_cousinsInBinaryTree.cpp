#include<vector>
#include<queue>
#include<map>
#include<iostream>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};



// Recursive function to check if two Nodes are siblings 
bool isSibling(TreeNode *root, int a, int b)
{
	// Base case 
	if (root == NULL)  return false;
	if (root->left == NULL && root->right == NULL)
		return false;

	if (root->left == NULL && root->right != NULL)
		return isSibling(root->right, a, b);
	if (root->right == NULL && root->left != NULL)
		 return isSibling(root->left, a, b);

	return ((root->left->val == a && root->right->val == b) ||
		(root->left->val == b && root->right->val == a)||
		isSibling(root->left, a, b)||
		isSibling(root->right, a, b));
		
}

// Recursive function to find level of Node 'ptr' in a binary tree 
int level(TreeNode *root, int ptr, int lev)
{
	// base cases 
	if (root == NULL) return 0;
	if (root->val == ptr)  return lev;
	
	// Return level if Node is present in left subtree 
	int l = level(root->left, ptr, lev + 1);
	if (l != 0)  return l;

	// Else search in right subtree 
	return level(root->right, ptr, lev + 1);
}

bool isCousins(TreeNode* root, int x, int y) {
	if (level(root, x, 1) == level(root, y, 1) && !isSibling(root, x, y))
		return true;
	return false;
}



int main() {
	TreeNode * root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->right = new TreeNode(4);
	root->right->right = new TreeNode(5);
	bool he = isCousins(root, 4, 5);
	system("pause");
}
