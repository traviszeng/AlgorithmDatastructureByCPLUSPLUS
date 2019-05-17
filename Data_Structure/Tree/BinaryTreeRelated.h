#pragma once
#include<queue>
/*���������ص��㷨����*/


struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
};


/**
	������������
*/
int treeDepth(TreeNode *root) {
	if (root == nullptr)
		return 0;
	int left = treeDepth(root->left);
	int right = treeDepth(root->right);
	return left > right ? left + 1 : right + 1;
}

/**
	��������Ŀ��
*/
int widthOfBinaryTree(TreeNode* root) {
	if (root == nullptr)
		return 0;
	std::queue<TreeNode*> Q;
	Q.push(root);

	int ans = 1;
	while (!Q.empty()) {
		int currentWidth = Q.size();  // ��ǰ��Ŀ��
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
