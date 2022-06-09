#pragma once
#include <iostream>
#include <ctime>

using namespace std;

struct Node
{
	Node(int data)
	{
		this->data = data;
		left = nullptr;
		right = nullptr;
	}
	int data;
	Node* left, * right;
};

class Tree
{
public:
	Tree();
	~Tree();

	void AddNode(int data);
	void ShowTree();
	void ClearTree();

	Node* PARENT(Node* root, Node* temp);
	Node* LEFTMOST_CHILD(Node* n);
	Node* RIGHT_SIBLING(Node* n);
	int LABEL(Node* n);
	Node* ROOT();

private:
	Node* root;
	void ShowNode(Node* node);
	void ClearNode(Node* node);
};

Tree::Tree()
{
	root = nullptr;
}

Tree::~Tree()
{
	ClearTree();
}

void Tree::AddNode(int data)
{
	if (root == nullptr)
	{
		root = new Node(data);
		return;
	}

	Node* current = this->root;

	while (true)
	{
		if (current->data > data)
			if (current->left != nullptr) current = current->left;
			else { current->left = new Node(data); break; }
		else
			if (current->right != nullptr) current = current->right;
			else { current->right = new Node(data); break; }
	}
}

void Tree::ShowTree()
{
	if (root == nullptr) return;
	cout << root->data << endl;
	ShowNode(root->left);
	ShowNode(root->right);
}

void Tree::ShowNode(Node* node)
{
	if (node == nullptr) return;
	cout << node->data << endl;
	ShowNode(node->left);
	ShowNode(node->right);
}

void Tree::ClearTree()
{
	if (root == NULL) return;
	ClearNode(root->left);
	ClearNode(root->right);
	delete root;
	root = nullptr;
}

void Tree::ClearNode(Node* node)
{
	if (node == NULL) return;
	ClearNode(node->left);
	ClearNode(node->right);
	delete node;
	node = nullptr;
}

Node* Tree::PARENT(Node* root, Node* temp)
{
	if (root == NULL) return nullptr;
	if (root->left == temp || root->right == temp)
		return root;

	return PARENT(root->left, temp);
	return PARENT(root->right, temp);
}

Node* Tree::LEFTMOST_CHILD(Node* n)
{
	while (n->left != nullptr)
	{
		n = n->left;
	}
	return n;
}

Node* Tree::RIGHT_SIBLING(Node* n)
{
	return PARENT(n, root)->right;
}

int Tree::LABEL(Node* n)
{
	return n->data;
}

Node* Tree::ROOT()
{
	return root;
}

int main()
{
	srand(time(0));
	Tree tree;
	int a;
	for (int i = 0; i < 5; i++)
	{
		a = rand() % 100;
		tree.AddNode(a);
	}

	cout << "Tree:" << endl;
	tree.ShowTree();

	return 0;
}
