#pragma once
#include<queue>
#include<vector>
#include<string>
#include<memory>
#include<sstream>
#include<list>
using namespace std;
/*���������ص��㷨����*/


struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
	TreeNode(int x) :val(x) {}
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

//p2�Ƿ�p1�ӽṹ
bool hasSubtree(TreeNode* p1, TreeNode* p2) {
	if (nullptr == p1 || p2 == nullptr)
		return false;
	return isSubTree(p1, p2)    // �ж��ӽṹ�Ƿ���ͬ
		|| hasSubtree(p1->left, p2)      // �ݹ�Ѱ���� A ������ B ���ڵ���ͬ���ӽڵ�
		|| hasSubtree(p1->right, p2);
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

//�ָ�������helper
TreeNode * buildTreeCore(std::vector<int> &preorder, int preorderStart, int preorderEnd,
	std::vector<int> &inorder, int inorderStart, int inorderEnd) {
	TreeNode* root = new TreeNode(preorder[preorderStart]);

	if (inorderStart == inorderEnd)
		return root;

	int rootLoc = inorderStart;
	for (int i = inorderStart; i <= inorderEnd; i++) {
		if (inorder[i] == root->val)
		{
			rootLoc = i;
			break;
			//rootLoc���Ϊ������
			//�ұ�Ϊ������
		}
	}
	int leftSize = rootLoc - inorderStart;
	int rightSize = inorderEnd - inorderStart - leftSize;
	if (leftSize > 0)
		root->left = buildTreeCore(preorder, preorderStart + 1, preorderStart + leftSize, inorder, inorderStart, inorderStart + leftSize - 1);
	if (rightSize > 0)
		root->right = buildTreeCore(preorder, preorderStart + leftSize + 1, preorderStart + leftSize + rightSize, inorder, rootLoc + 1, rootLoc + rightSize);
	return root;


}

//��ǰ�������������лָ�������
TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
	if (preorder.size() == 0 && inorder.size() == 0)
		return nullptr;
	if (preorder.size() != inorder.size())
		return nullptr;
	int length = preorder.size();
	return buildTreeCore(preorder, 0, length - 1, inorder, 0, length - 1);
}



/**
���л��ͷ����л�
*/
// Encodes a tree to a single string.
stringstream ss_serialize;
std::string serialize(TreeNode* root) {
	
	//ǰ�����
	
	traversal(root);

	return ss_serialize.str().c_str();
}

void traversal(TreeNode *root) {
	if (root == nullptr) {
		ss_serialize << "#";
		return;
	}
	ss_serialize << root->val;

	ss_serialize << " ";
	traversal(root->left);

	ss_serialize << " ";
	traversal(root->right);
}

// Decodes your encoded data to tree.
stringstream ss;
TreeNode* deserialize(std::string data) {
	if (data.length() < 1)
		return nullptr;
	ss << data;
	return dfs_bw();
}

TreeNode* dfs_bw() {
	if (ss.eof())
		return nullptr;

	string val;            // ��Ϊ "#"���� int �� char ���ն���������
	ss >> val;

	if (val == "#")
		return nullptr;

	TreeNode* node = new TreeNode{ stoi(val) };
	node->left = dfs_bw();
	node->right = dfs_bw();
	return node;
}

//��ȡ�Ӹ��ڵ㿪ʼ��·��
bool getPath(TreeNode* root, TreeNode* p, deque<TreeNode*>& path) {
	if (root == nullptr)
		return false;
	
	path.push_back(root);
	if (root == p)
		return true;

	bool isFound = false;
	if (!isFound)
		isFound = getPath(root->left, p, path);
	if (!isFound)
		isFound = getPath(root->right, p, path);

	if (!isFound)
		path.pop_back();
	return isFound;
	
}


/*Ѱ�������ڵ�������������(һ�������Ķ�����)
�ҳ������ڵ�Ӹ��ڵ㿪ʼ��·�����ҵ����һ����ͬ��
*/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (root == nullptr)
		return nullptr;
	
	deque<TreeNode*> pPath;
	deque<TreeNode*> qPath;

	bool isFoundp = getPath(root, p, pPath);
	bool isFoundq = getPath(root, q, qPath);
	
	int len = pPath.size() > qPath.size() ? qPath.size() : pPath.size();
	TreeNode * lowest = root;
	for (int i = 0; i < len; i++) {
		TreeNode* pTemp = pPath.front();
		TreeNode* qTemp = qPath.front();

		if (pTemp == qTemp) {
			lowest = pTemp;
			pPath.pop_front();
			qPath.pop_front();
		}
		else
			break;
	}

	return lowest;

}

/**
�ڶ�����������ֻҪ�ҵ���һ��p<root<q�Ľڵ㼴��
*/
TreeNode* lowestCommonAncestorBST(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (p->val > q->val)
	{
		TreeNode* temp = p;
		p = q;
		q = temp;
	}
	if (root == nullptr)
		return nullptr;
	if (p == nullptr || q == nullptr)
		return nullptr;
	if (root->val >= p->val&&root->val <= q->val)
		return root;
	if (root->val > q->val)
		return lowestCommonAncestorBST(root->left, p, q);
	else
		return lowestCommonAncestorBST(root->right, p, q);

}