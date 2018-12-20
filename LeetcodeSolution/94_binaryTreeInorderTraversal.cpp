#include<vector>
using namespace std;
/**
* Definition for a binary tree node.*/
struct TreeNode {    
	int val;
    TreeNode *left;
    TreeNode *right;
TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


	vector<int> inorderTraversal(TreeNode* root) {

		vector<int> result;
		if (root == nullptr)
			return result;
		vector<int> subresult = inorderTraversal(root->left);

		result.insert(result.end(), subresult.begin(), subresult.end());
		result.push_back(root->val);
		subresult = inorderTraversal(root->right);
		result.insert(result.end(), subresult.begin(), subresult.end());

		return result;

	}
