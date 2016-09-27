#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Node {
public:
	string key;
	Node * left;
	Node * right;
	Node()
	{
		key = -1;
		left = NULL;
		right = NULL;
	};
};

class Tree {
public:
	Node * root;
	Tree();
	void addNode(Node * n);
	void inOrder(Node * n);
	void preOrder(Node * n);
	void postOrder(Node * n);
	void addLeftNode(Node * leaf, Node * n);
	void addRightNode(Node * leaf, Node * n);
	void levelOrder(Node * root);
	void Level(Node * root, int level);
	int height(Node * node);
};

Tree::Tree() {
	root = NULL;
}

void Tree::addNode(Node * n) {
	root = n;
}

void Tree::addLeftNode(Node* leaf, Node * n) {
	leaf->left = n;
}

void Tree::addRightNode(Node* leaf, Node * n) {
	leaf->right = n;
}

void Tree::inOrder(Node * n) {
	if (n) {
		inOrder(n->left);
		cout << n->key << " ";
		inOrder(n->right);
	}
}

void Tree::preOrder(Node * n) {
	if (n) {
		cout << n->key << " ";
		preOrder(n->left);
		preOrder(n->right);
	}
}

void Tree::postOrder(Node * n) {
	if (n) {
		postOrder(n->left);
		postOrder(n->right);
		cout << n->key << " ";
	}
}

void Tree::levelOrder(Node * root)
{
	int h = height(root);
	for (int i = 1; i <= h; i++)
	{
		Level(root, i);
	}
}

void Tree::Level(Node * root, int level)
{
	if (root == NULL)
	{
		return;
	}
	if (level == 1)
	{
		cout << root->key << " ";
	}
	else if (level > 1)
	{
		Level(root->left, level - 1);
		Level(root->right, level - 1);
	}
}

int Tree::height(Node * n)
{
	if (n == NULL)
	{
		return 0;
	}
	else
	{
		int l = height(n->left);
		int r = height(n->right);

		if (l > r)
		{
			return(l + 1);
		}
		else
		{
			return(r + 1);
		}
	}
}

Tree* construct(vector<string> inOrder, vector<string> postOrder)
{
	int i = 0;
	while (inOrder[i] != postOrder[postOrder.size() - 1])
	{
		i++;
	}
	Tree * tree = new Tree();
	Node * n = new Node();
	n->key = inOrder[i];
	tree->addNode(n);
	if (inOrder.size() > 1)
	{
		if (inOrder.size() - 1 != i)
		{
			vector<string> right(inOrder.size() - i - 1);
			int k = 0;
			for (int j = i + 1; j < inOrder.size(); j++)
			{
				right[k] = inOrder[j];
				k++;
			}
			//string right = inOrder.substr(i + 1);
			vector<string> right1(right.size());
			k = 0;
			for (int j = i; j < i+right.size(); j++)
			{
				right1[k] = postOrder[j];
				k++;
			}
			//string right1 = postOrder.substr(i, right.size());
			Tree * rightTree = construct(right, right1);
			tree->addRightNode(n, rightTree->root);
		}
		if (i != 0)
		{
			vector<string> left(i);
			for (int j = 0; j < i; j++)
			{
				left[j] = inOrder[j];
			}
			//string left = inOrder.substr(0, i);
			vector<string> left1(i);
			for (int j = 0; j < i; j++)
			{
				left1[j] = postOrder[j];
			}
			//string left1 = postOrder.substr(0, i);
			Tree * leftTree = construct(left, left1);
			tree->addLeftNode(n, leftTree->root);
		}
	}
	return tree;
}

int main() {
	int numNodes;
	cin >> numNodes;
	vector<string> postOrder(numNodes);
	vector<string> inOrder(numNodes);
	for (int i = 0; i < numNodes; i++)
	{
		string key;
		cin >> key;
		postOrder[i] = key;
	}
	for (int i = 0; i < numNodes; i++)
	{
		string key;
		cin >> key;
		inOrder[i] = key;
	}

	Tree * tree = construct(inOrder, postOrder);

	tree->levelOrder(tree->root);
	cout << endl;
	return 0;
}