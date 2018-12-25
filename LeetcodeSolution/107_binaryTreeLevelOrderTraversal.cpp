/*
Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).

For example:
Given binary tree [3,9,20,null,null,15,7],
3
/ \
9  20
/  \
15   7
return its bottom-up level order traversal as:
[
[15,7],
[9,20],
[3]
]

**/

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

vector<vector<int>> levelOrderBottom(TreeNode* root) {
	vector<vector<int>> result;
	queue<TreeNode *> nodeQueue;
	if (root == NULL) {
		return result;
	}
	nodeQueue.push(root);
	while (!nodeQueue.empty()) {
		result.push_back(traversal(nodeQueue));

	}
	reverse(result.begin(), result.end());
	return result;

}



int main() {
	TreeNode *root = new TreeNode(3);
	levelOrderBottom(root);

}