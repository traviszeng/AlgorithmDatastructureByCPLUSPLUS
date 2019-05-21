#include<deque>
using namespace std;

struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
	TreeNode(int x) :val(x) {}
};

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