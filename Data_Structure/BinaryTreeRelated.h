#pragma once
#include<queue>
#include<vector>
#include<string>
#include<memory>
#include<sstream>
#include<list>
using namespace std;
/*与二叉树相关的算法内容*/


struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
	TreeNode(int x) :val(x) {}
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

//求最大宽度
int widthOfBinaryTree(TreeNode* root) {
	if (nullptr == root)
		return 0;
	std::deque<std::pair<TreeNode*, int>> d;


	d.push_back({ root,1 });
	int ans = 0;
	while (!d.empty()) {
		int cur_n = d.size();
		int cur_w = d.back().second - d.front().second + 1; //当前层的宽度
		ans = ans > cur_w ? ans : cur_w;

		//防止层数过高序号overflow
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

//最长路径长度
int longestRoute(TreeNode *root) {
	//遍历所有节点，经过该节点最长的路径为左子树深度+右子树深度+1
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

//p2是否p1子结构
bool hasSubtree(TreeNode* p1, TreeNode* p2) {
	if (nullptr == p1 || p2 == nullptr)
		return false;
	return isSubTree(p1, p2)    // 判断子结构是否相同
		|| hasSubtree(p1->left, p2)      // 递归寻找树 A 中与树 B 根节点相同的子节点
		|| hasSubtree(p1->right, p2);
}

bool isSubTree(TreeNode* p1, TreeNode* p2) {
	if (p2 == nullptr) return true;        // 注意这两个判断的顺序
	if (p1 == nullptr) return false;

	if (p1->val == p2->val)
		return isSubTree(p1->left, p2->left)    // 递归判断左右子树
		&& isSubTree(p1->right, p2->right);
	else
		return false;
}

//恢复二叉树helper
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
			//rootLoc左边为左子树
			//右边为右子树
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

//从前序和中序遍历序列恢复二叉树
TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
	if (preorder.size() == 0 && inorder.size() == 0)
		return nullptr;
	if (preorder.size() != inorder.size())
		return nullptr;
	int length = preorder.size();
	return buildTreeCore(preorder, 0, length - 1, inorder, 0, length - 1);
}



/**
序列化和反序列化
*/
// Encodes a tree to a single string.
stringstream ss_serialize;
std::string serialize(TreeNode* root) {
	
	//前序遍历
	
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

	string val;            // 因为 "#"，用 int 或 char 接收都会有问题
	ss >> val;

	if (val == "#")
		return nullptr;

	TreeNode* node = new TreeNode{ stoi(val) };
	node->left = dfs_bw();
	node->right = dfs_bw();
	return node;
}

//获取从根节点开始的路径
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


/*寻找两个节点的最近公共祖先(一般正常的二叉树)
找出两个节点从根节点开始的路径，找到最后一个相同的
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
在二叉搜索树中只要找到第一个p<root<q的节点即可
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