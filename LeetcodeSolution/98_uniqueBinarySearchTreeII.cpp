#include<iostream>
#include<vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<TreeNode*> generateTrees(int n, int st = 1)
{
	vector<TreeNode*> ans;
	if (n == st)
	{
		TreeNode* head = new TreeNode(n);
		ans.push_back(head);
		return ans;
	}
	for (int i = st; i <= n; i++)
	{
		vector<TreeNode*> leftTree;
		vector<TreeNode*> rightTree;
		if (i>st)leftTree = generateTrees(i - 1, st);
		if (i<n)rightTree = generateTrees(n, i + 1);
		for (int x = 0; x<leftTree.size(); x++)
		{
			for (int y = 0; y<rightTree.size(); y++)
			{
				TreeNode* head = new TreeNode(i);
				head->left = leftTree[x];
				head->right = rightTree[y];
				ans.push_back(head);
			}
		}
		for (int x = 0; x<leftTree.size() && rightTree.size() == 0; x++)
		{
			TreeNode* head = new TreeNode(i);
			head->left = leftTree[x];
			ans.push_back(head);
		}
		for (int y = 0; y<rightTree.size() && leftTree.size() == 0; y++)
		{
			TreeNode* head = new TreeNode(i);
			head->right = rightTree[y];
			ans.push_back(head);
		}
	}
	return ans;
}


int main() {
	vector<TreeNode*> ans = generateTrees(5);
	cout << ans.size();
	system("pause");
	//1 1  2 5 14 42 

}