#include<iostream>
#include<deque>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


int widthOfBinaryTree(TreeNode* root) {
	if (nullptr == root)
		return 0;
	std::deque<std::pair<TreeNode*,int>> d;
	

	d.push_back({ root,1 });
	int ans = 0;
	while (!d.empty()) {
		int cur_n = d.size();
		int cur_w = d.back().second - d.front().second + 1; //当前层的宽度
		ans = ans > cur_w ? ans : cur_w;
		
		//防止层数过高序号overflow
		int m = d.front().second;
		for (int i = 0; i < cur_n; i++) {
			
			auto p_node = d.front();
			d.pop_front();
			p_node.second -= m;
			d.push_back(p_node);
		}

		for (int i = 0; i < cur_n; i++) {
			auto p = d.front();
			d.pop_front();
			if (p.first->left != nullptr)
				d.push_back({ p.first->left, p.second * 2 });
			if (p.first->right != nullptr)
				d.push_back({ p.first->right, p.second * 2 + 1 });
		}
	}
	return ans;
}