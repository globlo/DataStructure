// circularQ.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

struct node
{
	string name;
	node* next;
	node(string nm)
	{
		this->name = nm;
		this->next = NULL;
	}
};

struct queue
{
	node* head;
	node* tail;

	queue()  //create totoal 7 node for circular
	{
		node* firstnode = new node("a");
		this->head = firstnode;
		this->tail = firstnode;

		for (int i = 0; i < 6; i++)
		{
			node* newnode = new node("k");
			tail->next = newnode;
			this->tail = newnode;
		}
		this->tail->next = this->head;
	}

	void printQ()
	{
		node* cu = this->head;
		while (cu != head)
		{
			cout << cu->name << endl;
			cu = cu->next;
		}
	}

};

int main()
{
	queue Q;

	Q.printQ();
    std::cout << "Hello World!\n";
}

