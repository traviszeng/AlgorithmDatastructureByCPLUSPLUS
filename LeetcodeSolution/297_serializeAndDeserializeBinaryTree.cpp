#include<sstream>
#include<iostream>
using namespace std;
struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
	TreeNode(int x) :val(x) {}
};


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