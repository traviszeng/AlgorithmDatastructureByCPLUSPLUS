struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
	TreeNode(int x) :val(x) {}
};

void traversal(TreeNode * root, int& num) {
	if (root == nullptr)
		return;
	num += 1;
	traversal(root->left, num);
	traversal(root->right, num);

}
int countNodes(TreeNode* root) {
	if (root == nullptr)
		return 0;
	int num = 0;
	traversal(root, num);
	return num;
}