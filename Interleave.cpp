#include <iostream>
using namespace std;

class Node {
public:
	int data;
	Node * next;

	Node(int d)
	{
		data = d;
		next = NULL;
	}

	Node(int d, Node * n)
	{
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

	void insertEnd(int d)
	{
		if (head == NULL)
		{
			Node * n = new Node(d, head);
			head = n;
			tail = n;
		}
		else
		{
			Node * n = new Node(d);
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
	LinkedList * iList = new LinkedList();
	
	int iCount;
	cin >> iCount;

	for (int i = 0; i < iCount; i++)
	{
		int data;
		cin >> data;
		iList->insertEnd(data);
	}

	int listCount;
	cin >> listCount;

	for (int i = 0; i < listCount; i++)
	{
		int step;
		cin >> step;
		int sCount;
		cin >> sCount;
		LinkedList * sList = new LinkedList();

		Node * current = iList->head;
	
		for (int i = 0; i < sCount; i++)
		{
			int data2;
			cin >> data2;

			sList->insertEnd(data2);
		}


		for (int i = 0; i < sCount; i++)
		{
			Node * insertNode = sList->head;
			Node * temp = insertNode->next;

			for (int j = 1; j < step && current->next != NULL; j++)
			{
				current = current->next;
			}

			iList->insertMiddle(current, sList->head);

			if (current->next->next != NULL)
			{
				current = current->next->next;
			}
			else
			{
				current = current->next;
			}
			sList->head = temp;
		}
	}
	
	iList->print();

    return 0;
}
