#pragma once
#include<queue>
/*与二叉树相关的算法内容*/


struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
};


/**
	求二叉树的深度
*/
int treeDepth(TreeNode *root) {
	if (root == nullptr)
		return 0;
	int left = treeDepth(root->left);
	int right = treeDepth(root->right);
	return left > right ? left + 1 : right + 1;
}

/**
	求二叉树的宽度
*/
int widthOfBinaryTree(TreeNode* root) {
	if (root == nullptr)
		return 0;
	std::queue<TreeNode*> Q;
	Q.push(root);

	int ans = 1;
	while (!Q.empty()) {
		int currentWidth = Q.size();  // 当前层的宽度
		ans = ans > currentWidth ? ans : currentWidth;

		for (int i = 0; i < currentWidth; i++) {
			auto p = Q.front();
			Q.pop();
			if (p->left)
				Q.push(p->left);
			if (p->right)
				Q.push(p->right);
		}
	}

	return ans;
}
