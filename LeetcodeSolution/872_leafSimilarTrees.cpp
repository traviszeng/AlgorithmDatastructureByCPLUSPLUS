#include<iostream>
#include<vector>
using namespace std;
struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;

};

void traversal(TreeNode* root, vector<int> &a) {
	if (root == NULL)
		return;
	if (root->left == nullptr&&root->right == nullptr)
		a.push_back(root->val);
	traversal(root->left, a);
	traversal(root->right, a);

}

bool leafSimilar(TreeNode* root1, TreeNode* root2) {
	vector<int> a1;
	vector<int> a2;
	traversal(root1, a1);
	traversal(root2, a2);
	if (a1.size() != a2.size())
		return false;
	for (int i = 0; i < a1.size(); i++) {
		if (a1[i] != a2[i])
			return false;
	}
	return true;
}