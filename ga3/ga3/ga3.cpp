// AVLtree.cpp : This file contains the 'main' function. Program execution begins and ends there.
// GA by Justin Santos, Karla Lemus, and Aiden Takei.

#include <iostream>
using namespace std;

struct node
{
	int data;
	node* left;
	node* right;
	int height;

	node(int newnum)
	{
		this->data = newnum;
		this->left = NULL;
		this->right = NULL;

		// CHANGE HEIGHT AT INIITIALIZATION
		this->height = 1;
	}
};

// A utility function that returns the max of two integers.
int max(int a, int b)
{
	return a > b ? a : b;
}

class AVL
{
private:
	node* root;
	node* insertInternal(node* n, int key);
	node* removeInternal(node* n, int key);
	void preOrderInternal(node* n);
public:
	int height(node* n);
	node* rightRotate(node* y);
	node* leftRotate(node* x);
	int getBalance(node* n);
	void insert(int key);
	void remove(int key);

	node* findMin(node* n);
	node* findMax(node* n);

	void preOrder();
};

// Utility recursive function to insert new nodes while balancing the tree, maintaining BTS and AVL.
node* AVL::insertInternal(node* n, int key)
{
	/* 1. Perform the normal BST insertion */
	if (n == NULL)
		return new node(key);

	if (key < n->data)
		n->left = insertInternal(n->left, key);
	else if (key > n->data)
		n->right = insertInternal(n->right, key);
	else // Equal keys are not allowed in BST
		return n;

	/* 2. Update height of this ancestor node */
	n->height = 1 + max(height(n->left), height(n->right));

	/* 3. Get the balance factor of this ancestor
		node to check whether this node became
		unbalnced */
	int balance = getBalance(n);

	// If this node becomes unbalanced, then
	// there are 4 cases

	// Left Left Case
	if (balance > 1 && key < n->left->data)
		return rightRotate(n);

	// Right Right Case
	if (balance < -1 && key > n->right->data)
		return leftRotate(n);

	// Left Right Case
	if (balance > 1 && key > n->left->data)
	{
		n->left = leftRotate(n->left);
		return rightRotate(n);
	}

	// Right Left Case
	if (balance < -1 && key < n->right->data)
	{
		n->right = rightRotate(n->right);
		return leftRotate(n);
	}

	/* return the (unchanged) node pointer */
	return n;
}

// Utility recrusive function to remove nodes from the AVL tree, maintaining BTS.
node* AVL::removeInternal(node* root, int key)
{

	// STEP 1: PERFORM STANDARD BST DELETE  
	if (root == NULL)
		return root;

	// If the key to be deleted is smaller  
	// than the root's key, then it lies 
	// in left subtree  
	if (key < root->data)
		root->left = removeInternal(root->left, key);

	// If the key to be deleted is greater  
	// than the root's key, then it lies  
	// in right subtree  
	else if (key > root->data)
		root->right = removeInternal(root->right, key);

	// if key is same as root's key, then  
	// This is the node to be deleted  
	else
	{
		// node with only one child or no child  
		if ((root->left == NULL) ||
			(root->right == NULL))
		{
			node* temp = root->left ?
				root->left :
				root->right;

			// No child case  
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else // One child case  
				*root = *temp; // Copy the contents of  
							   // the non-empty child  
			free(temp);
		}
		else
		{
			// node with two children: Get the inorder  
			// successor (smallest in the right subtree)  
			node* temp = findMin(root->right);

			// Copy the inorder successor's  
			// data to this node  
			root->data = temp->data;

			// Delete the inorder successor  
			root->right = removeInternal(root->right, temp->data);
		}
	}

	// If the tree had only one node 
	// then return  
	if (root == NULL)
		return root;

	// STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
	root->height = 1 + max(height(root->left),
		height(root->right));

	// STEP 3: GET THE BALANCE FACTOR OF  
	// THIS NODE (to check whether this  
	// node became unbalanced)  
	int balance = getBalance(root);

	// If this node becomes unbalanced,  
	// then there are 4 cases  

	// Left Left Case  
	if (balance > 1 && getBalance(root->left) >= 0)
		return rightRotate(root);

	// Left Right Case  
	if (balance > 1 && getBalance(root->left) < 0)
	{
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}

	// Right Right Case  
	if (balance < -1 && getBalance(root->right) <= 0)
		return leftRotate(root);

	// Right Left Case  
	if (balance < -1 && getBalance(root->right) > 0)
	{
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}

	return root;
}

// Utility recursive function used to display the items in pre order.
void AVL::preOrderInternal(node* n)
{
	if (n != nullptr)
	{
		cout << n->data << " ";
		preOrderInternal(n->left);
		preOrderInternal(n->right);
	}
}

// A utility function that returns the height of the tree.
int AVL::height(node* n)
{
	if (n == nullptr)
		return 0;
	return n->height;
}

// A utility function to right rotate subtree rooted with y.
node* AVL::rightRotate(node* y)
{
	node* x = y->left;
	node* t2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = t2;

	// Update heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// Return new root
	return x;
}

// A utility function to left rotate subtree rooted with x.
node* AVL::leftRotate(node* x)
{
	node* y = x->right;
	node* t2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = t2;

	// Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	// Return new root
	return y;
}

// Returns balance factor of node n.
int AVL::getBalance(node* n)
{
	if (n == NULL)
		return 0;
	return height(n->left) - height(n->right);
}

// Inserts a new key to the AVL tree.
void AVL::insert(int key)
{
	root = insertInternal(root, key);
}

// Removes a key from the AVL tree. Does nothing if key does not exist.
void AVL::remove(int key)
{
	root = removeInternal(root, key);
}

// Finds the minimum key node starting from root 'n'.
node* AVL::findMin(node* n)
{
	if (n == NULL)
		return nullptr;

	while (n->left != NULL)
		n = n->left;

	return n;
}

// Finds the maximum key node starting from root 'n'.
node* AVL::findMax(node* n)
{
	if (n == NULL)
		return nullptr;

	while (n->right != NULL)
		n = n->right;

	return n;
}

// Prints the nodes in pre order.
void AVL::preOrder()
{
	preOrderInternal(root);
	cout << endl;
}


int main()
{
	AVL* var = new AVL();

	var->insert(1);
	var->insert(2);
	var->insert(3);
	var->insert(36);
	var->insert(-4);
	var->insert(12);

	var->preOrder();

	var->remove(2);
	var->remove(36);

	var->preOrder();
}
