#include<deque>
using namespace std;

struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
	TreeNode(int x) :val(x) {}
};

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