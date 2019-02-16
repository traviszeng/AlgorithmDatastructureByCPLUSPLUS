#include<vector>
#include<queue>
#include<iostream>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode * buildTreeCore(vector<int> &postorder, int postorderStart, int postorderEnd,
	vector<int> &inorder, int inorderStart, int inorderEnd) {
	TreeNode* root = new TreeNode(postorder[postorderEnd]);

	if (inorderStart == inorderEnd)
		return root;

	int rootLoc = inorderStart;
	for (int i = inorderStart; i <= inorderEnd; i++) {
		if (inorder[i] == root->val)
		{
			rootLoc = i;
			break;
			//rootLoc×ó±ßÎª×ó×ÓÊ÷
			//ÓÒ±ßÎªÓÒ×ÓÊ÷
		}
	}
	int leftSize = rootLoc - inorderStart;
	int rightSize = inorderEnd - inorderStart - leftSize;
	if (leftSize>0)
		root->left = buildTreeCore(postorder, postorderStart + 1, postorderStart + leftSize, inorder, inorderStart, inorderStart + leftSize - 1);
	if (rightSize>0)
		root->right = buildTreeCore(postorder, postorderStart + leftSize + 1, postorderStart + leftSize + rightSize, inorder, rootLoc + 1, rootLoc + rightSize);
	return root;


}


TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
	if (postorder.size() == 0 && inorder.size() == 0)
		return nullptr;
	if (postorder.size() != inorder.size())
		return nullptr;
	int length = postorder.size();
	return buildTreeCore(postorder, 0, length - 1, inorder, 0, length - 1);
}

int main() {


	vector<int> post;
	post.push_back(9);
	post.push_back(15);
	post.push_back(7);
	post.push_back(20);
	post.push_back(3);
	vector<int> in;
	in.push_back(9);
	in.push_back(3);
	in.push_back(15);
	in.push_back(20);
	in.push_back(7);
	TreeNode *root = buildTree( in,post);
	system("pause");


}