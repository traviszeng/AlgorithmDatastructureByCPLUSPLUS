/**
* Definition for a binary tree node.*/
#include<iostream>
#include<vector>
#include<queue>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<int> traversal(queue<TreeNode *> &queue) {
	vector<int> temp;
	int size = queue.size();
	for (int i = 0; i < size; i++) {
		temp.push_back(queue.front()->val);
		if (queue.front()->left != NULL) queue.push(queue.front()->left);
		if (queue.front()->right != NULL) queue.push(queue.front()->right);
		queue.pop();
	}
	return temp;

}

vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
	vector<vector<int>> result;
	queue<TreeNode *> nodeQueue;
	if (root == NULL) {
		return result;
	}
	nodeQueue.push(root);
	while (!nodeQueue.empty()) {
		result.push_back(traversal(nodeQueue));

	}
	//reverse(result.begin(), result.end());
	for (int i = 1; i < result.size(); i += 2)
		reverse(result[i].begin(), result[i].end());
	return result;

}



int main() {
	TreeNode *root = new TreeNode(3);
	zigzagLevelOrder(root);

}