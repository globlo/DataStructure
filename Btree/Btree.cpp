// B_tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include<iostream> 
using namespace std;

// A BTree node 
class node
{
	int* datas;       // An array of keys 
	int datas_num;     // Current number of keys 

	int t;                  // Minimum degree (defines the range for number of keys) 
	node** eda; // An array of child pointers 
	bool leaf; // Is true when node is leaf. Otherwise false 
public:
	node(int data, int degree)
	{
		this->datas = new int[degree];   // number of data(array size) = degree(max of eda -1)

	}

	void insert_not_full(int newdata);

	// Make the BTree friend of this so that we can access private members of this 
	// class in BTree functions 
	friend class BTree;
};



// A BTree 
class BTree
{
	node* root; // Pointer to root node 
	int degree;       //
	int degree_Min;    // Minimum degree 
public:
	// Constructor (Initializes tree as empty) 
	BTree(int degree)
	{
		this->degree = degree;
		this->degree_Min = (degree + 1) / 2;    // shosu kiriage    i.e. 5/2 = 3
		root = NULL;
	}
	void insert(int newdata);

};
//dgree is max number of pointers to children nodes
void BTree::insert(int newdata)                              //just for root
{
	if (root == NULL)
	{
		root = new node(newdata, degree);
	}
	else if (root != NULL)
	{
		if (root->datas_num == degree - 1)    // #of data can contain only degree -1 as max
		{
			// sprint datas of root and put them to root's childrens
			
		}
		else if(root->datas_num  < degree)
		{
			// datas # can only be less than number of degree 
		}
	
		node* newnode = new node(newdata, degree);
	}
}
 
void node::insert_not_full(int newdata)
{
	int degree;

	if (leaf == true) // bottom node
	{
		for (int i = datas_num; i>=0; i--)
		{
			if (newdata < datas[i])
			{
			   datas[i+1] = datas[i];

			}
			else if (datas[i] < newdata)
			{
				datas[i + 1] = newdata;
				return;
			}
		}
	
		datas_num += 1;

		if ( datas_num == degree )   // # of data reach the max that can contain
		{
			// spllit the data into two nodes and back the middle data to the parents node

		}
	}
	else if (leaf == false)  // not bottom node
	{

	}
}

int main()
{

	std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file