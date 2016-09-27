#include <iostream>
using namespace std;

class Node {
public:
	int column;
	int data;
	Node * next;

	Node(int c, int d)
	{
		column = c;
		data = d;
		next = NULL;
	}

	Node(int c, int d, Node * n)
	{
		column = c;
		data = d;
		next = n;
	}
};

class LinkedList {
public:
	Node * head;
	Node * tail;
	LinkedList()
	{
		head = NULL;
		tail = NULL;
	}

	void insertHead(int c, int d)
	{
		Node * n = new Node(c, d, head);
		head = n;
	}

	void insertEnd(int c, int d)
	{
		if (head == NULL)
		{
			Node * n = new Node(c, d, head);
			head = n;
			tail = n;
		}
		else
		{
			Node * n = new Node(c, d);
			insertMiddle(tail, n);
		}
	}

	void insertMiddle(Node * beforeNode, Node * n)
	{
		if (beforeNode == tail)
		{
			Node * newNode = n;
			beforeNode->next = newNode;
			tail = newNode;
		}
		else
		{
			n->next = beforeNode->next;
			beforeNode->next = n;
		}
	}

	void print()
	{
		Node * current = head;
		while (current != NULL)
		{
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}
};

int main()
{
ios::sync_with_stdio(false);
	int row;
	cin >> row;
	LinkedList * matrix1 = new LinkedList[row];
	LinkedList * sum = new LinkedList[row];
	for (int i = 0; i < row; i++)
	{
		matrix1[i] = LinkedList();
		sum[i] = LinkedList();
		int n;
		cin >> n;
		for (int j = 0; j < n; j++)
		{
			int column;
			int data;
			cin >> column;
			cin >> data;
			matrix1[i].insertEnd(column, data);
			sum[i].insertEnd(column, data);
		}
	}

	cin >> row;
	LinkedList * matrix2 = new LinkedList[row];
	for (int i = 0; i < row; i++)
	{
		matrix2[i] = LinkedList();
		int n;
		cin >> n;
		for (int j = 0; j < n; j++)
		{
			int column;
			int data;
			cin >> column;
			cin >> data;
			matrix2[i].insertEnd(column, data);

			Node * current = sum[i].head;
			while (current != NULL)
			{
				if (current == sum[i].head && current->column > column)
				{
					sum[i].insertHead(column, data);
					break;
				}
				else if (current->column == column)
				{
					current->data += data;
					break;
				}
				else if (current->column < column && current->next == NULL)
				{
					sum[i].insertEnd(column, data);
					break;
				}
				else if (current->column < column && current->next->column > column)
				{
					Node * newNode = new Node(column, data);
					sum[i].insertMiddle(current, newNode);
					break;
				}
				current = current->next;
			}
		}
	}

	int search;
	cin >> search;

	int * arr = new int[search];

	for (int i = 0; i < search; i++)
	{
		int element;
		cin >> element;
		arr[i] = element;
	}
	for (int i = 0; i < search; i++)
	{
		for (int j = 0; j < row; j++)
		{
			Node * current = sum[j].head;
			while (current != NULL)
			{
				if (current->data == arr[i])
				{
					cout << j << " " << current->column << " ";
				}
				current = current->next;
			}
		}
		cout << endl;
	}


    return 0;
}