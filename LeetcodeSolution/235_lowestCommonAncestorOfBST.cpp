struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
	TreeNode(int x) :val(x) {}
};

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