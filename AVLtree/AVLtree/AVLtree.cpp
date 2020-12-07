// AVLtree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;


struct node
{
	int data;
	node* left;
	node* right;
	int height;

public:
	node(int newnum)
	{
		this->data = newnum;
		this->left = NULL;
		this->right = NULL;

		//CHANGE HEIGHT AT INIITIALIZATION
		this->height = 0;
	}

public: void setHeight(int height)
{
	if (this == NULL)
		return;
	this->height = height;
}

};

void insertNode(node* top, int num);

void MigiKaiten(node* tp);
void HidariKaiten(node* tp);
int depth_of(node* tp);
void get_display(node* cu, int I);
node* findMin(node* n);
node* findMax(node* n);
int deleteNode(int num, node* tp);

struct AVL {
	node* top = NULL;

	public: void insert(int num) {

	if (top == NULL) {
		node* newNode = new node(num);
		top = newNode;
	}
	else {
		insertNode(top, num);
	}
	}
	public :void display()
	{
		int i = 0;
		get_display(top, i);
		std::cout << "------------------------" << endl;

	}
	
public: void setTop(node* newtop)
{
	this->top = newtop;
}
	
};
node* get_balance(node* tp, AVL* t);

void get_display(node* cu, int I)
{
	if (cu == NULL)
		return;
	node* left_node = cu->left;
	node* right_node = cu->right;

	//cout << "depth is : " << nodeNum <<endl;     //depth from top of tree to the bottom ( the # of nodes)

	/*for (I; I < nodeNum; I++)
	{*/

		if (left_node == NULL && right_node == NULL)
		{
			cu->height = I;

			std::cout << " Height: " << cu->height << " -|- data: " << cu->data << endl;
		
			//cout << "------------------------" << endl;

			return;
		}
		else if (left_node != NULL && right_node == NULL)
		{
			cu->height = I;

			std::cout << " Height: " << cu->height  << " -|- data: " << cu->data << endl;
			get_display(cu->left,I +1);
		}
		else if (left_node == NULL && right_node != NULL)
		{
			cu->height = I;

			std::cout << " Height: " << cu->height << " -|- data: " << cu->data << endl;
			get_display(cu->right, I+1);
		}
		else if (left_node != NULL && right_node != NULL)
		{
			cu->height = I;

			std::cout << " Height: " << cu->height << " -|- data: " << cu->data << endl;

			get_display(left_node,  I+1);
			get_display(right_node, I+1);
			//I = I + 1;
		}

	//}

}


void insertNode(node* top, int num)
{
	//cu->data = num;
	////compare from the top if the # is less or more
	//node* top;
	node* tmp = top;
	node* newNode = new node(num);

	int height = 0;

	while (tmp != NULL)
	{
		if (num > tmp->data)     // right
		{
			if (tmp->right != NULL) {
				tmp = tmp->right;

				height = height + 1;
	
				continue;
			}
			else {
				height = height + 1;

				newNode->setHeight(height);
				tmp->right = newNode;

			}
		}
		else if (num < tmp->data )  // left
		{
			if (tmp->left != NULL) {
				tmp = tmp->left;

				height = height + 1;

				continue;
			}
			else {
				height = height + 1;

				newNode->setHeight(height);
				tmp->left = newNode;
			}
		}
		else if(tmp->data == num)
		{
			return;
		}

	}


}

void MigiKaiten(node* tp)
{
	node* tp_left = tp->left;                    // make this to tp

	node* tp_left_right =tp_left->right;    	//make this to head->left;


	tp_left->right = tp;                       
	/*
	        y              x
		   / \            / \ 
		  x   z          a1  y
	     / \                  \
        a1  a2                 z
	*/


	tp->left = tp_left_right;
	/*
			x              x
		   / \            / \
		  a1   y          a1  y
		      / \            / \
		         z          a2  z
	*/
	
	//change height
	int tp_height = tp->height;

	tp->setHeight(tp_left->height);
	tp_left->setHeight(tp_height);      //new top!

	tp_left->left->setHeight(tp->height);     //new tp->height which is +1 from root


}

void HidariKaiten(node* tp)
{
	node* tp_right = tp->right;                    // make this to tp

	node* tp_right_left = tp_right->left;    	//make this to head->right;


	tp_right->left = tp;


	tp->right = tp_right_left;

	//change height
	int tp_height = tp->height;

	tp->setHeight(tp_right->height);   //(tp datta)
	tp_right->setHeight(tp_height);      //new top!


	tp_right->right->setHeight(tp->height);     //new tp->height which is +1 from root

}


node* get_balance(node* tp, AVL* t)   //return new tp
{
	//node* tp = t->top;
	node* tp_left = tp->left;
	node* tp_right = tp->right;

	/*how many nodes from tp->left and how many nodes from tp->right  including the initial node itself*/
	int hidari = depth_of(tp_left);
	int migi = depth_of(tp_right);
	
	node* currentTOP = tp;
	node* newTP =currentTOP;
	if (hidari > 2)                //make this recursively
	{
		 newTP = get_balance(tp_left, t);
		
		t->setTop(currentTOP);
		currentTOP->left = newTP;
		hidari = depth_of(tp->left);
		newTP = currentTOP;
	}
	if (migi > 2)
	{
		newTP = get_balance(tp_right, t);
		
		t->setTop(currentTOP);
		currentTOP->right = newTP;
		migi = depth_of(tp->right);
		newTP = currentTOP;

	}

	int sa = hidari - migi;

	//Left  case  : leftDepth > rightDepth
	if (sa == 2)       
	{
		if (tp_left->right==NULL&&tp_left->left != NULL && tp_left->left->data < tp_left->data)   //Left Left case
		{
			MigiKaiten(tp);

			t->setTop(tp_left);
			newTP = t->top;

			//t.top = tp_left;                           // change top of  the tree

			//return tp_left;
		}
		else if (tp_left->right != NULL && (tp_left->right->data > tp_left->data))  // Left Right case
		{
			node* tp_left_right = tp_left->right;

			HidariKaiten(tp_left);
			//tp->left = tp_left->right;
			tp->left = tp_left_right;
			MigiKaiten(tp);

			t->setTop(tp_left_right);
			newTP = t->top;

			//t.top = tp_left->right;                         
			//return tp_left->right;
		}
	}
	//Right case  : leftDepth < rightDepth
	else if (sa == -2)
	{
		if (tp_right->left== NULL &&tp_right->right != NULL &&tp_right->right->data > tp_right->data)       //Right Right case
		{
			HidariKaiten(tp);

			t->setTop(tp_right);
			newTP = t->top;

			//t.top = tp_right;       
			//return tp_right;
		}
		else if (tp_right->left != NULL && (tp_right->left->data < tp_right->data))    //Right Left case
		{
			node* tp_right_left = tp_right->left;

			MigiKaiten(tp_right);
			//tp->right = tp_right->left;
			tp->right = tp_right_left;
			HidariKaiten(tp);

			t->setTop(tp_right_left);
			newTP = t->top;

			//t.top = tp_right->left;    
			//return tp_right->left;

		}
	
	}
	return newTP;
	
		
}



/* Compute the "maxDepth" of a tree -- the number of
	nodes along the longest path from the root node
	down to the farthest leaf node.*/
int depth_of(node* tp)
{
	node* tmp = tp;
	//int num = cu->data;
	 
	int depth_count = 1;   // 1 b/c want to include the root node itself

	if (tmp == NULL)
		return 0;
	else if ((tmp->right == NULL) && (tmp->left == NULL))   //iranaikamo
		return 1;

	while (tmp != NULL)
	{
		if ((tmp->left != NULL) && (tmp->right == NULL) )
		{
			tmp = tmp->left;
			depth_count = depth_count + 1;
		}
		else if ((tmp->right != NULL) && (tmp->left == NULL))
		{
			tmp = tmp->right;
			depth_count = depth_count + 1;
		}
		else if ((tmp->right != NULL) && (tmp->left != NULL))
		{
			int depth_left = depth_of(tmp->left);     //just for compare not for store the height;
			int depth_right = depth_of(tmp->right);   //just for compare not for store the height;


			if (depth_left > depth_right)   //  deeper depth(height) on left  
			{
				depth_count = depth_count + 1;            //subeteno +1 ha  root no height
				tmp = tmp->left;

			}
			else if (depth_left < depth_right)  // deeper depth(height) on right
			{
				depth_count = depth_count + 1;
				tmp = tmp->right;

			}
			else if (depth_left == depth_right)
			{
				depth_count = depth_count+ depth_left;     
				
				break;
			}
		
		}
		else if ((tmp->right == NULL) && (tmp->left == NULL))
		{
			break;
		}
	
	}

	return depth_count;

}

int deleteNode(int num, node* tp)
{
	node* prev = NULL;
	node* tmp = tp;

	while (tmp != NULL)
	{
		if (num > tmp->data)     // right
		{
			if (tmp->right != NULL) 
			{
				prev = tmp;
				tmp = tmp->right;
				continue;
			}
			else
				break;  //reach to NULL then break , there is no tha value exist in tree

		}
		else if (num < tmp->data)  // left
		{
			if (tmp->left != NULL)
			{
				prev = tmp;
				tmp = tmp->left;
				continue;
			}
			else 
				break;

		}
		else if (tmp->data == num)
		{
			node* want_del = tmp;
			//copy maxNOde and delete here

			if (tmp->left != NULL)
			{
				node* MxNode = findMax(tmp->left);    //has  to do something if tmp->left == NULL
				tmp->data = MxNode->data;            //copy the value and paste it into the current node

				if (MxNode->data == want_del->left->data)
				{
					tmp->left = MxNode->left;     
				}
				else if (MxNode->data == want_del->left->right->data)
				{
					tmp->left->right = NULL;
				}

			}
			else if (tmp->left == NULL && tmp->right == NULL)
			{
				prev->left = NULL;
				return 0;
			}
			else 
			{
				node* minNode = findMin(tmp->right);

				if (prev == NULL) // when only the root node
				{
					tp->data = minNode->data;
				}
				else
				{
					prev->right = minNode;
					tmp = minNode;
				}
			}
		}

	}
	return 0;
}

node* findMin(node* n)
{
	if (n == NULL)
		return nullptr;

	while (n->left != NULL)
		n = n->left;

	return n;
}
node* findMax(node* n)
{
	if (n == NULL)
		return nullptr;

	while (n->right != NULL)
		n = n->right;

	return n;
}

int main()
{
	
	std::cout << endl<<"Height counted from root which is 0 " << endl<<endl;
	AVL* t = new AVL;

	t->insert(20);
	get_balance(t->top, t);
	t->display();                 //kekkamiru


	t->insert(15);
	get_balance(t->top, t);
	t->display();

	t->insert(16);
	get_balance(t->top,t);//kekkamiru
	t->display();                 //kekkamiru

	t->insert(27);
	get_balance(t->top, t);
	t->display();

	t->insert(30);
	get_balance(t->top, t);
	t->display();

	t->insert(5);
	get_balance(t->top, t);
	t->display();

	t->insert(35);
	get_balance(t->top, t);
	t->display();

	t->insert(67);
	get_balance(t->top, t);
	t->display();

	/*deleteNode(20, t->top);
	get_balance(t->top, t);
	t->display();*/


	//t->display(); 



	t->insert(25);
	get_balance(t->top, t);
	t->display();

	t->insert(26);
	get_balance(t->top, t);
	t->display();
	

	t->insert(21);
	get_balance(t->top, t);
	t->display();

	//t->insert(22);
	//get_balance(t->top, t);
	//t->display();


	//t->insert(2);
	//get_balance(t->top, t);
	//t->display();

	//get_balance(t.top);


}

