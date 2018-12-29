#include<iostream>
#include<vector>
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//统计node的子树sum
int sumOfNodes(TreeNode *root);
int findTilt(TreeNode *root, int& tilt) {
	if (root == NULL)
		return 0;
	int left = findTilt(root->left,tilt);
	int right = findTilt(root->right, tilt);
	tilt += abs(left -right );
	return left+right+root->val;
}

int findTilt(TreeNode* root) {
	int tilt = 0;
	if (root == NULL)
		return 0;
	if (root->left == NULL&&&root->right == NULL)
		return 0;
	
	findTilt(root, tilt);
	return tilt;
}


int sumOfNodes(TreeNode *root) {
	int sum = 0;
	if (root == NULL)
		return 0;
	//if (root->left == NULL&&root->right == NULL)
	sum += root->val;
	if(root->left!=NULL)
		sum += sumOfNodes(root->left);
	if(root->right!=NULL)
		sum += sumOfNodes(root->right);
	
	return sum;

}

int main() {
	TreeNode *root = new TreeNode(1);
	root->left = new TreeNode(2);
	root->right = new TreeNode(3);
	root->left->left = new TreeNode(4);
	root->right->left = new TreeNode(5);
	cout << findTilt(root);
	system("pause");
}