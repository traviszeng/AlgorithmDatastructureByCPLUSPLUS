#pragma once
#include<queue>
#include<vector>
#include<string>
#include<stack>
#include<memory>
#include<sstream>
#include<iostream>
#include<list>
using namespace std;
/*与二叉树相关的算法内容*/


struct TreeNode {
	TreeNode *left;
	TreeNode *right;
	int val;
	TreeNode(int x) :val(x) {}
};


/**
	求二叉树的深度
*/
int treeDepth(TreeNode *root) {
	if (root == nullptr)
		return 0;
	int left = treeDepth(root->left);
	int right = treeDepth(root->right);
	return left > right ? left + 1 : right + 1;
}

/**
	求二叉树的宽度
*/
int widthOfBinaryTree(TreeNode* root) {
	if (root == nullptr)
		return 0;
	std::queue<TreeNode*> Q;
	Q.push(root);

	int ans = 1;
	while (!Q.empty()) {
		int currentWidth = Q.size();  // 当前层的宽度
		ans = ans > currentWidth ? ans : currentWidth;

		for (int i = 0; i < currentWidth; i++) {
			auto p = Q.front();
			Q.pop();
			if (p->left)
				Q.push(p->left);
			if (p->right)
				Q.push(p->right);
		}
	}

	return ans;
}

//求最大宽度
int widthOfBinaryTree(TreeNode* root) {
	if (nullptr == root)
		return 0;
	std::deque<std::pair<TreeNode*, int>> d;


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

//最长路径长度
int longestRoute(TreeNode *root) {
	//遍历所有节点，经过该节点最长的路径为左子树深度+右子树深度+1
	if (nullptr == root)
		return 0;
	int max = treeDepth(root->left) + treeDepth(root->right) + 1;
	int left = 0;
	int right = 0;
	if (root->left) {
		left = longestRoute(root->left);
		max = max > left ? max : left;
	}
	if (root->right) {
		right = longestRoute(root->right);
		max = max > right ? max : right;
	}
	return max;

}

//p2是否p1子结构
bool hasSubtree(TreeNode* p1, TreeNode* p2) {
	if (nullptr == p1 || p2 == nullptr)
		return false;
	return isSubTree(p1, p2)    // 判断子结构是否相同
		|| hasSubtree(p1->left, p2)      // 递归寻找树 A 中与树 B 根节点相同的子节点
		|| hasSubtree(p1->right, p2);
}

bool isSubTree(TreeNode* p1, TreeNode* p2) {
	if (p2 == nullptr) return true;        // 注意这两个判断的顺序
	if (p1 == nullptr) return false;

	if (p1->val == p2->val)
		return isSubTree(p1->left, p2->left)    // 递归判断左右子树
		&& isSubTree(p1->right, p2->right);
	else
		return false;
}

//恢复二叉树helper
TreeNode * buildTreeCore(std::vector<int> &preorder, int preorderStart, int preorderEnd,
	std::vector<int> &inorder, int inorderStart, int inorderEnd) {
	TreeNode* root = new TreeNode(preorder[preorderStart]);

	if (inorderStart == inorderEnd)
		return root;

	int rootLoc = inorderStart;
	for (int i = inorderStart; i <= inorderEnd; i++) {
		if (inorder[i] == root->val)
		{
			rootLoc = i;
			break;
			//rootLoc左边为左子树
			//右边为右子树
		}
	}
	int leftSize = rootLoc - inorderStart;
	int rightSize = inorderEnd - inorderStart - leftSize;
	if (leftSize > 0)
		root->left = buildTreeCore(preorder, preorderStart + 1, preorderStart + leftSize, inorder, inorderStart, inorderStart + leftSize - 1);
	if (rightSize > 0)
		root->right = buildTreeCore(preorder, preorderStart + leftSize + 1, preorderStart + leftSize + rightSize, inorder, rootLoc + 1, rootLoc + rightSize);
	return root;


}

//从前序和中序遍历序列恢复二叉树
TreeNode* buildTree(std::vector<int>& preorder, std::vector<int>& inorder) {
	if (preorder.size() == 0 && inorder.size() == 0)
		return nullptr;
	if (preorder.size() != inorder.size())
		return nullptr;
	int length = preorder.size();
	return buildTreeCore(preorder, 0, length - 1, inorder, 0, length - 1);
}



/**
序列化和反序列化
*/
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

//获取从根节点开始的路径
bool getPath(TreeNode* root, TreeNode* p, deque<TreeNode*>& path) {
	if (root == nullptr)
		return false;
	
	path.push_back(root);
	if (root == p)
		return true;

	bool isFound = false;
	if (!isFound)
		isFound = getPath(root->left, p, path);
	if (!isFound)
		isFound = getPath(root->right, p, path);

	if (!isFound)
		path.pop_back();
	return isFound;
	
}


/*寻找两个节点的最近公共祖先(一般正常的二叉树)
找出两个节点从根节点开始的路径，找到最后一个相同的
*/
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
	if (root == nullptr)
		return nullptr;
	
	deque<TreeNode*> pPath;
	deque<TreeNode*> qPath;

	bool isFoundp = getPath(root, p, pPath);
	bool isFoundq = getPath(root, q, qPath);
	
	int len = pPath.size() > qPath.size() ? qPath.size() : pPath.size();
	TreeNode * lowest = root;
	for (int i = 0; i < len; i++) {
		TreeNode* pTemp = pPath.front();
		TreeNode* qTemp = qPath.front();

		if (pTemp == qTemp) {
			lowest = pTemp;
			pPath.pop_front();
			qPath.pop_front();
		}
		else
			break;
	}

	return lowest;

}

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

//中序遍历递归
void inorderTraversalRecursively(TreeNode* root) {
	if (root == nullptr)
		return;
	inorderTraversalRecursively(root->left);
	std::cout << root->val;
	inorderTraversalRecursively(root->right);
}

//中序遍历非递归
void inorderTraversalIteratively(TreeNode* root) {
	if (root == nullptr)
		return;
	stack<TreeNode *> s;
	TreeNode* temp = root;
	while (!s.empty() || temp) {
		//一直遍历到左子树最下边，边遍历边保存根节点到栈中
		while (temp) {
			s.push(temp);
			temp = temp->left;
		}
		//当temp为空时，说明已经到达左子树最下边，这时需要出栈了  
		if (!s.empty()) {
			temp = s.top();
			s.pop();
			cout << temp->val;
			//进入右子树，开始新的一轮左子树遍历(这是递归的自我实现)  
			temp = temp->right;
		}
	}
}

//前序遍历递归
void preorderTraversalRecursively(TreeNode *root) {
	if (root == nullptr)
		return;
	cout << root->val;
	preorderTraversalRecursively(root->left);
	preorderTraversalRecursively(root->right);
}

void preorderTraversalRecursively(TreeNode* root) {
	if (root == nullptr)
		return;
	stack<TreeNode*> s;
	TreeNode* temp = root;
	while (!s.empty() || temp) {
		while (temp) {
			//边遍历边打印
			cout << temp;
			s.push(temp);
			temp = temp->left;
		}
		if (!s.empty()) {
			temp = s.top();
			s.pop();
			temp = temp->right;
		}

	}
}

//后序遍历递归
void postorderTraversalRecursively(TreeNode *root) {
	if (root == nullptr)
		return;
	postorderTraversalRecursively(root->left);
	postorderTraversalRecursively(root->right);
	cout << root->val;
}


//后序遍历  
void PostOrderWithoutRecursion(TreeNode* root)
{
	if (root == NULL)
		return;
	stack<TreeNode*> s;
	//pCur:当前访问节点，pLastVisit:上次访问节点  
	TreeNode* pCur, *pLastVisit;
	//pCur = root;  
	pCur = root;
	pLastVisit = NULL;
	//先把pCur移动到左子树最下边  
	while (pCur)
	{
		s.push(pCur);
		pCur = pCur->left;
	}
	while (!s.empty())
	{
		//走到这里，pCur都是空，并已经遍历到左子树底端(看成扩充二叉树，则空，亦是某棵树的左孩子)  
		pCur = s.top();
		s.pop();
		//一个根节点被访问的前提是：无右子树或右子树已被访问过  
		if (pCur->right == NULL || pCur->right == pLastVisit)
		{
			cout  << pCur->val;
			//修改最近被访问的节点  
			pLastVisit = pCur;
		}
		/*这里的else语句可换成带条件的else if:
		else if (pCur->left == pLastVisit)//若左子树刚被访问过，则需先进入右子树(根节点需再次入栈)
		
		*/
		else
		{
			//根节点再次入栈  
			s.push(pCur);
			//进入右子树，且可肯定右子树一定不为空  
			pCur = pCur->right;
			while (pCur)
			{
				s.push(pCur);
				pCur = pCur->left;
			}
		}
	}
	cout << endl;
}


//传入一个一维数组 返回其组成huffman树的根节点
template<typename ElemType>
struct BTreeNode* CreateHuffman(ElemType a[], int n)
{
	int i, j;
	struct BTreeNode **b, *q;
	b = malloc(n * sizeof(struct BTreeNode));
	for (i = 0; i < n; i++)
	{
		b[i] = malloc(sizeof(struct BTreeNode));
		b[i]->data = a[i];
		b[i]->left = b[i]->right = NULL;
	}
	for (i = 1; i < n; i++)
	{
		int k1 = -1, k2;
		for (j = 0; j < n; j++)
		{
			if (b[j] != NULL && k1 == -1)
			{
				k1 = j;
				continue;
			}
			if (b[j] != NULL)
			{
				k2 = j;
				break;
			}
		}
		for (j = k2; j < n; j++)
		{
			if (b[j] != NULL)
			{
				if (b[j]->data < b[k1]->data)
				{
					k2 = k1;
					k1 = j;
				}
				else if (b[j]->data < b[k2]->data)
					k2 = j;
			}
		}
		q = malloc(sizeof(struct BTreeNode));
		q->data = b[k1]->data + b[k2]->data;
		q->left = b[k1];
		q->right = b[k2];
		b[k1] = q;
		b[k2] = NULL;
	}
	free(b);
	return q;
}

void ConvertNode(TreeNode* root, TreeNode** plast) {
	if (root == nullptr) {
		return;
	}
	TreeNode * pCurrent = root;
	if (pCurrent->left != nullptr) {
		ConvertNode(pCurrent->left, plast);
	}

	if (pCurrent->right != nullptr)
		ConvertNode(pCurrent->right, plast);


	pCurrent->left = *plast;
	if (*plast != nullptr)
		(*plast)->right = pCurrent;
	*plast = pCurrent;

}



//将二叉树按照后序遍历转成双向链表
TreeNode* Convert(TreeNode* root) {
	if (root == nullptr) {
		return nullptr;
	}
	TreeNode* lastNode = nullptr;
	ConvertNode(root, &lastNode);

	TreeNode *pCurrent = lastNode;
	pCurrent->right = nullptr;
	while (pCurrent != nullptr&&pCurrent->left != nullptr)
		pCurrent = pCurrent->left;

	return pCurrent;

}