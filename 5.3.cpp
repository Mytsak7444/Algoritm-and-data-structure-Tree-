#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

class Node
{
public:
	Node()
	{
		left = nullptr;
		right = nullptr;
	};
	Node(int probability, string symbol)
	{
		this->probability = probability;
		this->symbol = symbol;
	}

	Node* left, * right;
	string symbol;
	int probability;
};

class Tree
{
public:
	Tree(char symbol[], int probability[], int size);
	~Tree();

	void Print();

	string Coding(string str);
	string DeCoding(string str);

private:
	void DeleteNode(Node* node);
	int FindMinProb(int* temp);
	string FindCode(char t);
	Node* root;
	char* symbol;
	int* probability;
	int SIZE;
};

Tree::Tree(char symbol[], int probability[], int size)
{
	this->SIZE = size;
	this->symbol = new char[SIZE];
	this->probability = new int[SIZE];
	root = nullptr;
	for (int i = 0; i < SIZE; i++)
	{
		this->symbol[i] = symbol[i];
		this->probability[i] = probability[i];
	}

	int* temp = new int[2 * SIZE];

	for (int i = 0; i < SIZE; i++)
		temp[i] = probability[i];

	for (int i = SIZE; i < 2 * SIZE; i++)
		temp[i] = 0;

	Node* node = new Node[2 * SIZE];
	int k = SIZE;
	for (int i = 0; i < SIZE; i++)
	{
		node[i].probability = probability[i];
		node[i].symbol = symbol[i];
	}

	while (k != 2 * SIZE - 1)
	{
		int t1 = FindMinProb(temp);
		int t2 = FindMinProb(temp);

		node[k].probability = node[t1].probability + node[t2].probability;
		node[k].symbol = node[t1].symbol + node[t2].symbol;

		if (node[t1].probability < node[t2].probability)
		{
			node[k].left = &node[t1];
			node[k].right = &node[t2];
		}
		else
		{
			node[k].left = &node[t2];
			node[k].right = &node[t1];
		}

		temp[k] = node[k].probability;

		root = &node[k];
		k++;
	}
}

Tree::~Tree()
{
	if (root == NULL) return;
	DeleteNode(root->left);
	DeleteNode(root->right);
	root = nullptr;
}

void Tree::Print()
{
	for (int i = 0; i < SIZE; i++)
	{
		cout << symbol[i] << " = " << FindCode(symbol[i]) << endl;
	}
}

string Tree::Coding(string str)
{
	string result;
	for (int i = 0; i < str.length(); i++)
	{
		result += FindCode(str[i]);
	}
	return result;
}

string Tree::DeCoding(string str)
{
	string result;
	while (str.length() != 0)
	{
		Node* temp = root;
		while (temp->left != nullptr && temp->right != nullptr)
		{
			if (str[0] == '0')
			{
				temp = temp->left;
				str.erase(0, 1);
			}
			else if (str[0] == '1')
			{
				temp = temp->right;
				str.erase(0, 1);
			}

			else
				return result;
		}
		result += temp->symbol;
	}
	return result;
}

string Tree::FindCode(char t)
{
	string result;
	Node* temp = root;
	while (temp->left != nullptr && temp->right != nullptr)
	{
		if (temp->left->symbol.find(t) != string::npos)
		{
			temp = temp->left;
			result += '0';
		}
		else if (temp->right->symbol.find(t) != string::npos)
		{
			temp = temp->right;
			result += '1';
		}
		else
			return result;
	}
	return result;
}

int Tree::FindMinProb(int* temp)
{
	int mIndex = 0, mData = temp[0];
	int i = 1;

	while (mData == 0)
	{
		mData = temp[i];
		mIndex = i;
		i++;
	}

	for (int i = 0; i < 2 * SIZE; i++)
		if (temp[i] < mData && temp[i] != 0)
		{
			mData = temp[i];
			mIndex = i;
		}

	temp[mIndex] = 0;

	return mIndex;
}

void Tree::DeleteNode(Node* node)
{
	if (node == NULL) return;
	DeleteNode(node->left);
	DeleteNode(node->right);
}

int main()
{
	SetConsoleOutputCP(1251);

	char symbol[5] = { 'a','b','c','d','e' };
	int probability[5] = { 15,3,50,25,7 };
	string str;
	Tree tree(symbol, probability, 5);

	cout << "Інформація:" << endl;
	tree.Print();

	cout << "\nКодування: ";
	cin >> str;
	cout << tree.Coding(str) << endl;

	cout << "\nДекодування: ";
	cin >> str;
	cout << tree.DeCoding(str) << endl;

	return 0;
}
