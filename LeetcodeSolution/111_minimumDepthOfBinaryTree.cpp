/**
* Definition for a binary tree node.*/
#include<iostream>
#include<queue>
using namespace std;
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };


int minDepth(TreeNode* root) {
	if (root == NULL)
		return 0;

	if (root->left == NULL&&root->right == NULL)
		return 1;

	if (root->left == NULL &&root->right != NULL)
		return minDepth(root->right) + 1;

	else if(root->right == NULL &&root->left != NULL)
		return minDepth(root->left) + 1;
	
	else
		return minDepth(root->left)<minDepth(root->right) ? minDepth(root->left) + 1 : minDepth(root->right) + 1;
}

/**
使用队列 宽度优先BFS
*/
int minDepth2(TreeNode* root) {
	if (root == NULL) return 0;
	queue<TreeNode*> Q;
	Q.push(root);
	int i = 0;
	while (!Q.empty()) {
		i++;
		int k = Q.size();
		for (int j = 0; j<k; j++) {
			TreeNode* rt = Q.front();
			if (rt->left) Q.push(rt->left);
			if (rt->right) Q.push(rt->right);
			Q.pop();
			if (rt->left == NULL && rt->right == NULL) return i;
		}
	}
	return -1; //For the compiler thing. The code never runs here.
}

int main() {
	TreeNode *root = new TreeNode(1);
	root->left = new TreeNode(2);
	cout << minDepth(root);
	system("pause");
}