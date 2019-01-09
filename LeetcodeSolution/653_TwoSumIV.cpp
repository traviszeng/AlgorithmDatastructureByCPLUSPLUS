/**
* Definition for a binary tree node.
*/ 
#include<iostream>
#include<map>
using namespace std;
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

void traversal(TreeNode* root, map<int, int> &bmap);

bool findTarget(TreeNode* root, int k) {
	map<int, int> BSTmap;
	traversal(root, BSTmap);
	map<int, int>::iterator iter;
	for (iter = BSTmap.begin(); iter != BSTmap.end(); iter++) {
		if (BSTmap.size() < 2)
			return false;
		if (BSTmap.find(k - iter->first) != BSTmap.end()&&k!=(iter->first*2))
			return true;
	}
	return false;
}

void traversal(TreeNode* root, map<int, int> &bmap) {
	if (root == NULL)
		return;
	bmap[root->val] = root->val;
	traversal(root->left,bmap);
	traversal(root->right,bmap);

}

bool findTarget2(TreeNode* root, int k) {
	map<int, int> m;
	return helper(root, k, m);
}
bool helper(TreeNode* &root, int k, map<int, int>& m)
{
	if (!root)
		return false;
	if (m.find(k - root->val)->second > 0)
		return true;
	m.insert(pair<int, int>(root->val, 1));
	return helper(root->left, k, m) || helper(root->right, k, m);
}

int main() {
	TreeNode *node = new TreeNode(2);
	node->right = new TreeNode(3);
	cout<<findTarget(node, 6);
	system("pause");

}