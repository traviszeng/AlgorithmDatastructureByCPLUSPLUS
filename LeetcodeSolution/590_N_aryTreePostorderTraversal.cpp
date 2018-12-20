#include <vector>
#include<iostream>
using namespace std;
// Definition for a Node.
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

vector<int> postorder(Node* root) {

	vector<int> result;
	if (root == nullptr)
		return result;


	for (int i = 0; i < root->children.size(); i++) {
		vector<int> subresult = postorder(root->children[i]);
		result.insert(result.end(), subresult.begin(), subresult.end());
	}
	
	result.push_back(root->val);


	return result;
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

	vector<int> traversal = postorder(root);
	for  (int i = 0;  i < traversal.size();  i++)
	{
		cout << traversal[i] << " ";
	}
	system("pause");

}