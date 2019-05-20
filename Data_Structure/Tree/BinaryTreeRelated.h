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

//�������
int widthOfBinaryTree(TreeNode* root) {
	if (nullptr == root)
		return 0;
	std::deque<std::pair<TreeNode*, int>> d;


	d.push_back({ root,1 });
	int ans = 0;
	while (!d.empty()) {
		int cur_n = d.size();
		int cur_w = d.back().second - d.front().second + 1; //��ǰ��Ŀ��
		ans = ans > cur_w ? ans : cur_w;

		//��ֹ�����������overflow
		int m = d.front().second;
		for (int i = 0; i < cur_n; i++) {

			auto p_node = d.front();
			d.pop_front();
			p_node.second -= m;
			d.push_back(p_node);
		}

		for (int i = 0; i < cur_n; i++) {
			auto p = d.front();
			d.pop_front();
			if (p.first->left != nullptr)
				d.push_back({ p.first->left, p.second * 2 });
			if (p.first->right != nullptr)
				d.push_back({ p.first->right, p.second * 2 + 1 });
		}
	}
	return ans;
}

//�·������
int longestRoute(TreeNode *root) {
	//�������нڵ㣬�����ýڵ����·��Ϊ���������+���������+1
	if (nullptr == root)
		return 0;
	int max = treeDepth(root->left) + treeDepth(root->right) + 1;
	int left = 0;
	int right = 0;
	if (root->left) {
		left = longestRoute(root->left);
		max = max > left ? max : left;
	}
	if (root->right) {
		right = longestRoute(root->right);
		max = max > right ? max : right;
	}
	return max;

}


bool hasSubtree(TreeNode* p1, TreeNode* p2) {
	if (nullptr == p1 || p2 == nullptr)
		return false;
	return isSubTree(p1, p2)    // �ж��ӽṹ�Ƿ���ͬ
		|| HasSubtree(p1->left, p2)      // �ݹ�Ѱ���� A ������ B ���ڵ���ͬ���ӽڵ�
		|| HasSubtree(p1->right, p2);
}

bool isSubTree(TreeNode* p1, TreeNode* p2) {
	if (p2 == nullptr) return true;        // ע���������жϵ�˳��
	if (p1 == nullptr) return false;

	if (p1->val == p2->val)
		return isSubTree(p1->left, p2->left)    // �ݹ��ж���������
		&& isSubTree(p1->right, p2->right);
	else
		return false;
}

