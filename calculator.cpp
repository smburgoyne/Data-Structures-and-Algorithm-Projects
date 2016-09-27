#include <iostream>
#include <string>
#include <math.h>
#include <cctype>
#include <sstream>
#include <unordered_map>
using namespace std;


class Node {
public:
	char data;
	int order;
	Node * next;
};
class Stack {
public:
	Node * head;
	Stack();
	void insert(char d, int o);
	void remove();
	void print();
};
Stack::Stack()
{
	head = NULL;
}
void Stack::insert(char d, int o)
{
	Node * n = new Node;
	n->data = d;
	n->order = o;
	n->next = head;
	head = n;
}
void Stack::remove()
{
	if (head != NULL)
	{
		Node * n = head;
		head = head->next;
		delete n;
	}
}
void Stack::print()
{
	Node * n = head;
	while (n != NULL)
	{
		cout << n->data << " ";
		n = n->next;
	}
	cout << endl;
}
class dNode {
public:
	double data;
	dNode * next;
};
class dStack {
public:
	dNode * head;
	dStack();
	void dInsert(double d);
	void dRemove();
	void dPrint();
};
dStack::dStack()
{
	head = NULL;
}
void dStack::dInsert(double d)
{
	dNode * n = new dNode;
	n->data = d;
	n->next = head;
	head = n;
}
void dStack::dRemove()
{
	if (head != NULL)
	{
		dNode * n = head;
		head = head->next;
		delete n;
	}
}
void dStack::dPrint()
{
	dNode * n = head;
	while (n != NULL)
	{
		cout << n->data << " ";
		n = n->next;
	}
	cout << endl;
}

double eval(double d1, double d2, char operate) {
	if (operate == '*')
	{
		return d2 * d1;
	}
	if (operate == '/')
	{
		return d2 / d1;
	}
	if (operate == '+')
	{
		return d2 + d1;
	}
	if (operate == '-')
	{
		return d2 - d1;
	}
	if (operate == '^')
	{
		return pow(d2, d1);
	}
}

string expression(string line, unordered_map<string, double>  * u)
{
	dStack * outStack = new dStack();
	Stack * opStack = new Stack();
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] == ' ')
		{
			i++;
		}
		if (isdigit(line[i]) || line[i] == '.')
		{
			string number;
			number += line[i];
			while (isdigit(line[i + 1]) || line[i + 1] == '.')
			{
				number += line[i + 1];
				i++;
			}
			double num = stod(number);
			outStack->dInsert(num);
		}
		if (isalpha(line[i]))
		{
			string var;
			var += line[i];
			while (isalpha(line[i + 1]))
			{
				var += line[i + 1];
				i++;
			}
			if (u->count(var) == 0)
			{
				return "Undeclared-Variable";
			}
			else
			{
				outStack->dInsert(u->at(var));
			}
		}
		if (line[i] == '^')
		{
			opStack->insert('^', 3);
		}
		if (line[i] == '*')
		{
			if (opStack->head != NULL)
			{
				while (opStack->head->order >= 2)
				{
					double d1 = outStack->head->data;
					outStack->dRemove();
					double d2 = outStack->head->data;
					outStack->dRemove();
					char op = opStack->head->data;
					opStack->remove();

					double d = eval(d1, d2, op);
					outStack->dInsert(d);

					if (opStack->head == NULL)
					{
						break;
					}
				}
			}
			opStack->insert('*', 2);
		}
		if (line[i] == '/')
		{
			if (opStack->head != NULL)
			{
				while (opStack->head->order >= 2)
				{
					double d1 = outStack->head->data;
					outStack->dRemove();
					double d2 = outStack->head->data;
					outStack->dRemove();
					char op = opStack->head->data;
					opStack->remove();

					if (d1 != 0)
					{
						double d = eval(d1, d2, op);
						outStack->dInsert(d);
						if (opStack->head == NULL)
						{
							break;
						}
					}
					else
					{
						return "Division-By-Zero";
					}
				}
			}
			opStack->insert('/', 2);
		}
		if (line[i] == '+')
		{
			if (opStack->head != NULL)
			{
				while (opStack->head->order >= 1)
				{
					double d1 = outStack->head->data;
					outStack->dRemove();
					double d2 = outStack->head->data;
					outStack->dRemove();
					char op = opStack->head->data;
					opStack->remove();

					double d = eval(d1, d2, op);
					outStack->dInsert(d);
					if (opStack->head == NULL)
					{
						break;
					}
				}
			}
			opStack->insert('+', 1);
		}
		if (line[i] == '-')
		{
			if (opStack->head != NULL)
			{
				while (opStack->head->order >= 1)
				{
					double d1 = outStack->head->data;
					outStack->dRemove();
					double d2 = outStack->head->data;
					outStack->dRemove();
					char op = opStack->head->data;
					opStack->remove();

					double d = eval(d1, d2, op);
					outStack->dInsert(d);
					if (opStack->head == NULL)
					{
						break;
					}
				}
			}
			opStack->insert('-', 1);
		}
		if (line[i] == '(')
		{
			opStack->insert('(', 0);
		}
		if (line[i] == ')')
		{
			while (opStack->head->data != '(')
			{
				double d1 = outStack->head->data;
				outStack->dRemove();
				double d2 = outStack->head->data;
				outStack->dRemove();
				char op = opStack->head->data;
				opStack->remove();

				if (d1 != 0 || op != '/')
				{
					double d = eval(d1, d2, op);
					outStack->dInsert(d);
				}
				else
				{
					return "Division-By-Zero";
				}
			}
			opStack->remove();
		}
	}

	while (opStack->head != NULL)
	{
		double d1 = outStack->head->data;
		outStack->dRemove();
		double d2 = outStack->head->data;
		outStack->dRemove();
		char op = opStack->head->data;
		opStack->remove();

		if (d1 != 0 || op != '/')
		{
			double d = eval(d1, d2, op);
			outStack->dInsert(d);
		}
		else
		{
			return "Division-By-Zero";
		}
	}

	return to_string(outStack->head->data);
}
int main()
{
	unordered_map<string, double>  * u = new unordered_map<string, double>();
	bool quit = false;
	while (!quit)
	{
		string l;
		getline(cin, l);
		if (l.substr(0, 4) == "quit")
		{
			quit = true;
			break;
		}
		if (l.substr(0, 3) == "let")
		{
			int i = 4;
			while (isalpha(l[i + 1]))
			{
				i++;
			}
			string var = l.substr(4, i - 3);

			while (l[i] != '=')
			{
				i++;
			}
			string exp = l.substr((i + 1), (l.size() - i - 1));

			if (!isalpha(expression(exp, u)[0]))
			{
				string value = expression(exp, u);

				if (u->count(var) == 0)
				{
					pair<string, double> newVar(var, stod(value));
					u->insert(newVar);
				}
				else
				{
					u->at(var) = stod(value);
				}
			}
			else
			{
				cout << expression(l, u) << endl;
			}
		}
		else
		{
			cout << expression(l, u) << endl;
		}
	}
	return 0;
}