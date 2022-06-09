#include <iostream>

using namespace std;

struct Node
{
	Node(string data)
	{
		this->data = data;
		left = nullptr;
		right = nullptr;
	}
	string data;
	Node* left, * right;
};

class Tree
{
public:
	Tree();
	Tree(string str);
	~Tree();

	void AddNode(string data);
	void ShowTree();
	void ClearTree();

	Node* PARENT(Node* root, Node* temp);
	Node* LEFTMOST_CHILD(Node* n);
	Node* RIGHT_SIBLING(Node* n);
	string LABEL(Node* n);
	Node* ROOT();

	void PREORDER(Node* n);
	void POSTORDER(Node* n);
	void INORDER(Node* n);

private:
	Node* root;
	void ShowNode(Node* node);
	void ClearNode(Node* node);
};

Tree::Tree()
{
	root = nullptr;
}

Tree::Tree(string str)
{
	root = new Node("");
	Node* temp = root;
	Node* temp2 = nullptr;
	string t;
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			t.push_back(str[i]);
			temp->left = new Node(t);
			temp2 = temp;
			temp = temp->left;
			t.clear();
		}
		else if (str[i] == ')')
		{
			temp2 = PARENT(root, temp);
			temp = temp2;
		}
		else if (str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/')
		{
			temp->data = str[i];
			temp->right = new Node("");
			temp2 = temp;
			temp = temp->right;
		}
		else
		{
			temp->data = str[i];
			temp = temp2;
		}
	}
}

Tree::~Tree()
{
	ClearTree();
}

void Tree::AddNode(string data)
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
	cout << root->data;
	ShowNode(root->left);
	ShowNode(root->right);
}

void Tree::ShowNode(Node* node)
{
	if (node == nullptr) return;
	cout << node->data;
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
	if (n == NULL) return nullptr;
	while (n->left != nullptr)
	{
		n = n->left;
	}
	return n;
}

Node* Tree::RIGHT_SIBLING(Node* n)
{
	if (n == NULL) return nullptr;
	return PARENT(root, n)->right;
}

string Tree::LABEL(Node* n)
{
	return n->data;
}

Node* Tree::ROOT()
{
	return root;
}

void Tree::PREORDER(Node* n)
{
	if (n == nullptr) return;
	cout << n->data;
	PREORDER(n->left);
	PREORDER(n->right);
}

void Tree::POSTORDER(Node* n)
{
	if (n == nullptr) return;
	POSTORDER(n->left);
	POSTORDER(n->right);
	cout << n->data;
}

void Tree::INORDER(Node* n)
{
	if (n == nullptr) return;
	INORDER(n->left);
	cout << n->data;
	INORDER(n->right);
}

int main()
{
	Tree tree("((b*(a*(a-c))))/(b*(b+c)))");

	cout << "IPREORDER:" << endl;
	tree.PREORDER(tree.ROOT());

	cout << "\n\n" << "POSTORDER:" << endl;
	tree.POSTORDER(tree.ROOT());

	cout << "\n\n" << "INORDER:" << endl;
	tree.INORDER(tree.ROOT());

	return 0;
}
