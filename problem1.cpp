#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Node class
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
	void inOrder(Node* n);
	void preOrder(Node* n);
	void postOrder(Node* n);
	void addLeftNode(Node * leaf, Node * n);
	void addRightNode(Node * leaf, Node * n);
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

void Tree::inOrder(Node* n) {
	if (n) {
		inOrder(n->left);
		cout << n->key << " ";
		inOrder(n->right);
	}
}

void Tree::preOrder(Node* n) {
	if (n) {
		cout << n->key << " ";
		preOrder(n->left);
		preOrder(n->right);
	}
}

void Tree::postOrder(Node* n) {
	if (n) {
		postOrder(n->left);
		postOrder(n->right);
		cout << n->key << " ";
	}
}

int main() {
	Tree* tree = new Tree();
	int numNodes;
	cin >> numNodes;
	vector<Node*> Nodes(numNodes);
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
		Node * n = new Node();
		n->key = key;
		Nodes[i] = n;
		Left[i] = left;
		Right[i] = right;
	}
	for (int i = 0; i < numNodes; i++)
	{
		if (Left[i] != -1)
		{
			Nodes[i]->left = Nodes[Left[i]];
			if (Nodes[Left[i]] == tree->root)
			{
				tree->root = Nodes[i];
			}
		}
		if (Right[i] != -1)
		{
			Nodes[i]->right = Nodes[Right[i]];
			if (Nodes[Right[i]] == tree->root)
			{
				tree->root = Nodes[i];
			}
		}
		if (tree->root == NULL)
		{
			tree->root = Nodes[i];
		}
	}
	tree->postOrder(tree->root);
	cout << endl;
	tree->inOrder(tree->root);
	cout << endl;
	tree->preOrder(tree->root);
	cout << endl;
	return 0;
}