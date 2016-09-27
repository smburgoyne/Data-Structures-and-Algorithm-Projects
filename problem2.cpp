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
	void levelOrder(Node * root);
	void Level(Node * root, int level);
	int height(Node * node);
	void addLeftNode(Node * leaf, Node * n);
	void addRightNode(Node * leaf, Node * n);
	Node* constructTree(string key, int left, int right, vector<string> Nodes, vector<int> Left, vector<int> Right);
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
Node* Tree::constructTree(string key, int left, int right, vector<string> Nodes, vector<int> Left, vector<int> Right)
{
	Node * n = new Node();
	n->key = key;
	if (left != -1)
	{
		n->left = constructTree(Nodes[left], Left[left], Right[left], Nodes, Left, Right);
	}
	if (right != -1)
	{
		n->right = constructTree(Nodes[right], Left[right], Right[right], Nodes, Left, Right);
	}

	return n;
}

int main() {
	Tree* tree = new Tree();
	int numNodes;
	cin >> numNodes;
	vector<string> Nodes(numNodes);
	vector<int> Left(numNodes);
	vector<int> Right(numNodes);
	for (int i = 0; i < numNodes; i++)
	{
		string key;
		int left;
		int right;
		cin >> key;
		cin >> left;
		cin >> right;
		Nodes[i] = key;
		Left[i] = left;
		Right[i] = right;
	}
	tree->root = tree->constructTree(Nodes[0], Left[0], Right[0], Nodes, Left, Right);

	tree->levelOrder(tree->root);
	cout << endl;
	return 0;
}