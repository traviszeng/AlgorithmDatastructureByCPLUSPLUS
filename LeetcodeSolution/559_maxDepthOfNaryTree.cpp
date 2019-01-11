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

int maxDepth(Node* root) {
	if (root == NULL)
		return 0;
	if (root->children.size() == 0)
		return 1;
	int max;
	for (int i = 0; i < root->children.size(); i++) {
		
	}
}