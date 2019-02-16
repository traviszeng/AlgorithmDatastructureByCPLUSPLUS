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

TreeNode * buildTreeCore(vector<int> &preorder, int preorderStart, int preorderEnd, 
	vector<int> &inorder,int inorderStart, int inorderEnd) {
	TreeNode* root = new TreeNode(preorder[preorderStart]);
	
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
	int rightSize = inorderEnd - inorderStart  - leftSize;
	if(leftSize>0)
		root->left = buildTreeCore(preorder, preorderStart + 1, preorderStart + leftSize, inorder, inorderStart, inorderStart + leftSize-1);
	if(rightSize>0)
		root->right = buildTreeCore(preorder, preorderStart + leftSize + 1, preorderStart + leftSize  + rightSize, inorder, rootLoc + 1, rootLoc + rightSize);
	return root;


}


TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	if (preorder.size() == 0 && inorder.size() == 0)
		return nullptr;
	if (preorder.size() != inorder.size())
		return nullptr;
	int length = preorder.size();
	return buildTreeCore(preorder, 0, length-1,inorder, 0, length-1);
}

int main() {
	
	
	vector<int> pre;
	pre.push_back(1);
	pre.push_back(2);
	pre.push_back(3);
	//pre.push_back(4);
	//pre.push_back(7);
	vector<int> in;
	in.push_back(3);
	in.push_back(2);
	in.push_back(1);
	//in.push_back(4);
	//in.push_back(7);
	TreeNode *root = buildTree(pre, in);
	system("pause");


}