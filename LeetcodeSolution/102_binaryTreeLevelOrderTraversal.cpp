#include<vector>
#include<queue>
#include<iostream>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
void traversal(TreeNode *root, vector<vector<int>> &result, queue<TreeNode*> &q);

vector<vector<int>> levelOrder(TreeNode* root) {
	vector<vector<int>> result;
	queue<TreeNode*> nodeQueue;
	traversal(root, result,nodeQueue);
	return result;
}

void traversal(TreeNode *root, vector<vector<int>> &result,queue<TreeNode*> &q) {
	if (root == NULL)
		return;
	q.push(root);
	while (!q.empty()) {//每清空一次代表queue里面的全部节点都添加进vector中
		int size = q.size();
		vector<int> temp;
		for (int i = 0; i < size; i++) {
			temp.push_back(q.front()->val);
			if (q.front()->left != NULL)
				q.push(q.front()->left);
			if (q.front()->right != NULL)
				q.push(q.front()->right);
			q.pop();
		}
		result.push_back(temp);
	}

}


int main() {
	TreeNode *root = new TreeNode(3);
	root->left = new TreeNode(9);
	root->right = new TreeNode(20);
	root->right->left = new TreeNode(1);
	root->right->right = new TreeNode(12);
	levelOrder(root);

}