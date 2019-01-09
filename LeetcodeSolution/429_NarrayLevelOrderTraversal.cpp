// Definition for a Node.
#include<iostream>
#include<vector>
#include<queue>
#include<cassert>
using namespace std;
class Node {
public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};

void helper(vector<vector<int>> &result, Node *root, int level);
vector<vector<int>> levelOrder(Node* root) {
	vector<vector<int>> result;
	if (root == NULL)
		return result;
	helper(result, root,1);
	return result;
}


void helper(vector<vector<int>> &result, Node *root,int level) {
	if (root == NULL)
		return;
	if (result.size() < level) {
		vector<int> sub;
		result.push_back(sub);
	}
	result[level - 1].push_back(root->val);
	for (int i = 0; i < root->children.size(); i++) {
		helper(result, root->children[i], level + 1);
	}


}

int main() {
	Node* node = new Node();
	node->val = 3;
	Node* node1 = new Node();
	node1->val = 4;
	Node* node2 = new Node();
	node2->val = 5;
	vector<Node *> children;
	children.push_back(node1);
	children.push_back(node2);
	children.push_back(node);
	Node *root = new Node(1, children);

	levelOrder(root);
	system("pause");

}

