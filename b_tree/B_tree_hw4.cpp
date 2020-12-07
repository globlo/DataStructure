// B_tree_hw4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <stdio.h>
#include <iostream>
#include <list>
#include <vector>
#include <iterator> 
#include <fstream>
#include "ArgumentManager.h"
//#include <sstream>
//#include <cmath>
#include <algorithm>
//#include <bits/stdc++.h> 
using namespace std;


class node {
public:

	vector<int> data;
	vector<node*> children;
	node* parent;

public:
	void insertNum(int num) {

		if (this->data.empty()) {
			this->data.push_back(num);
			return;
		}

		for (int i = 0; i < this->data.size(); i++) {
			if (this->data.at(i) > num) {
				/*if (i == 0) {
					this->data.insert(this->data.begin(), num);
					return;
				}*/
				this->data.insert((this->data.begin() + i), num);
				return;
			}
			else if (this->data.at(i) == num)                     // no need to insert
				return;
		}
		this->data.push_back(num);
	}
	void addChild(node* child) {

		child->parent = this;

		if (this->children.empty()) {
			this->children.push_back(child);
			return;
		}
		if (child->data.empty())
			return;

		for (int i = 0; i < this->children.size(); i++) {
			if (this->children.at(i)->data.at(0) > child->data.at(0) ){                       // not sure here tbh
				/*if (i == 0) {
					this->data.insert(this->data.begin(), num);
					return;
				}*/
				this->children.insert((this->children.begin() + i), child);
				return;
			}
			//else if (this->children.at(i)->data.at(0) == child->data.at(0))                     // no need to insert
			//	return;
		}
		this->children.push_back(child);
	}

};


class bTree {
	node* root = NULL;
	int degree;
	int degree_Min;
public:
	vector<vector<int>> kontena/*(vector<int>())*/;
	int** arr;
public:
	bTree(int degree)
	{
		this->degree = degree;
		this->degree_Min = ((degree + 1) / 2);
		root = NULL;
	}
	void insertData(int newData) {

		if (root == NULL) {

			node* newNode = new node;
			newNode->insertNum(newData);
			newNode->parent = NULL;

			this->root = newNode;
			return;
		}
		//check root node if root node can still insert
		else if (root->children.empty())
		{
			if (root->data.size() < (degree - 1))
			{
				root->insertNum(newData);
				return;
			}
			else if (root->data.size() == (degree - 1))
			{
				root->insertNum(newData);

				split_mke_new( root);
				return;

			}
		}
		else if (!root->children.empty()) // child exist
		{
			
			node* ha_to_isert = find_ha(newData, root);
			//cout << "newData is "<<newData<<", --- ha is " << ha_to_isert->data.at(0) << endl;
			/* +++++++++++*/
			for (int i = 0; i < ha_to_isert->data.size(); i++)
				if (ha_to_isert->data.at(i) == newData)    return;


			insert_recursively(newData, ha_to_isert);
			
		}

		//cout << "nothing happend yet" << endl;
		return;
	}
    bool insert_recursively(int num, node* tp);
	void split_mke_new(/*int newData,*/ node* cu);
	void split_ptrtoTp(/*int newData,*/ node* cu);

	node* find_ha(int num, node* tp);

	void printB(node* tp, int level);
	void print()  {printB(this->root, 1);}

	int countLev(node* tp, int level);
	void count_lev() { cout<<endl<<" max level is: "<<countLev(this->root, 1); }

	void prt_all_lev(node* tp);
	void print_all_lev() { prt_all_lev(this->root); }
	void just_store(node* tp, int level);

	void prt_a_lev(node* tp , int levelNum, ofstream& y);                            //file outpput
	void printLev(int lev, ofstream& y) { prt_a_lev(this->root, lev, y); }

	void print_traverse(node* tp, ofstream& y);                                        //file output
	void traverse(ofstream& y) { print_traverse(this->root, y); }

};
node* bTree::find_ha(int num, node* tp)                //find ha from the selected top
{
	node* currentNode = tp;
	node* ha = currentNode;


	if (currentNode->children.size() ==0)
		return currentNode;
	if (num > currentNode->data.back())
		return ha = find_ha(num , currentNode->children.back());

		for (int i = 0; i < currentNode->data.size(); i++)  
		{
		
			if (num < currentNode->data.at(i))
			{
				currentNode = currentNode->children.at(i);

				return ha = find_ha(num, currentNode);
			}
			else if (num == currentNode->data.at(i))
				return ha = currentNode;
	
		}
		
	
	return ha;
}


bool bTree::insert_recursively(int num, node* cu)  // sended the childred of the top
{
	
	if (cu->data.size() == degree)  // recursived
	{
		if (cu->parent == NULL)  // recursive saisyu no node  // this case happen when cu == root
		{
			//cu->insertNum(num);
			split_mke_new( cu);
			return true;
		}
		else if (cu->parent->data.size() < degree-1)
		{
			//cu->insertNum(num);
			split_ptrtoTp( cu);
			return true;
		}
		else if (cu->parent->data.size() == degree - 1)
		{
			//cu->insertNum(num);
			split_ptrtoTp(cu);

			insert_recursively(num, cu->parent);
			return true;
		}
		return true;
	}

	if (cu->data.size() < (degree - 1))
	{
		for (int i = 0; i < cu->data.size(); i++)     // the case of child node is full, but how you figure out which child node is it?
		{
			if (num == cu->data.at(i) )
				return true;
			else if (num < cu->data.at(i))
			{
				cu->data.insert(cu->data.begin()+i, num);
				return true;
			}
		}
		cu->data.push_back(num);
		return true;

	}
	else if (cu->data.size() == (degree - 1))
	{
		for (int i = 0; i < cu->data.size(); i++)
			if (cu->data.at(i) == num)
				return false;
	

		if (cu->parent->data.size() < (degree-1 ) )  
		{
			cu->insertNum(num);
			split_ptrtoTp( cu);
			
			return true;
			
		}
		else if (cu->parent->data.size() == degree-1)
		{
			cu->insertNum(num);

			split_ptrtoTp(cu);

			
			insert_recursively(num, cu->parent);  // send num but would not be used after recursive 
			return true;
		}

		return false;

	}

}
void bTree::split_ptrtoTp(/*int newData,*/ node* cu)  // this allows to make migi but keep hidari and hidari(cu)->top
{
	//cu->insertNum(newData);                               // toriaezu insert into the datas
	int middleIndex = ((cu->data.size() - 1) / 2);
	vector<node*> data = cu->children;

	cu->parent->insertNum(cu->data.at(middleIndex));   //send middle data to the parent b/c parent has data.size < degree -1
	cu->data.erase(cu->data.begin() + middleIndex);    //erae the data from the tp

	node* hidariNode = cu;
	node* migiNode = new node;


	int size = cu->data.size();  // tmp vector that saved the data from tp
	for (int i = middleIndex; i < size; i++) migiNode->insertNum(cu->data.at(i));

	for (int i = size-1; i >=  middleIndex; i--)
	{
		hidariNode->data.erase(cu->data.begin() + i);
	}

	hidariNode->parent = cu->parent;
	migiNode->parent = cu->parent;
	cu->parent->addChild(migiNode);


	if (cu->children.size() != 0)
	{
		hidariNode->children.clear();

		for (int i = 0; i < middleIndex +1;i++ ) //hidari
		{
			node* childH = data.at(i);
			hidariNode->addChild(childH);
		}
		for (int i = middleIndex + 1; i < data.size(); i++)   // migi
		{
			node* childM = data.at(i);
			migiNode->addChild(childM);
			//hidariNode->children.erase(cu->children.begin() + i);
			//hidariNode->children.erase(cu->children.begin() + middleIndex+1);                         ////kokokokokoklo
		}
		
		
	}

	return;
}

void bTree::split_mke_new(/*int newData,*/ node* cu)  // this split half the current node and make  a newNode on top
{
	int middleIndex = ((degree - 1) / 2);

	//cu->insertNum(newData);
	vector<int> data = cu->data;

	int middleData = data.at(middleIndex);
	data.erase(data.begin() + middleIndex);

	node* newRoot = new node;
	newRoot->data.push_back(middleData);
	newRoot->parent = NULL;


	node* migiNode = new node;
	node* hidariNode = new node;

	hidariNode->parent = newRoot;
	migiNode->parent = newRoot;

	for (int i = 0; i < middleIndex; i++) hidariNode->insertNum(data.at(i));
	for (int i = middleIndex; i < data.size(); i++) migiNode->insertNum(data.at(i));

	newRoot->addChild(hidariNode);
	newRoot->addChild(migiNode);

	this->root = newRoot;

	if (cu->children.size() != 0)
	{

		for (int i = 0; i < middleIndex+1; i++)   // changing ptr_to_childrens 
		{
			node* childH = cu->children.at(i);
			hidariNode->addChild(childH);
	
		}
		for (int i = middleIndex +1; i < cu->children.size(); i++)
		{
			node* childM = cu->children.at(i);
			migiNode->addChild(childM);
		}
	}
	return;
}

int main(int argc, char* argv[])
{
	

	ArgumentManager am(argc, argv);
	string finputName = am.get("input");
	string foutputName = am.get("output");
	string filecommand = am.get("command");

	cout << finputName << endl;
	cout << foutputName << endl;

	ifstream file_cmd;             
	file_cmd.open(filecommand);

	ifstream file_val;                
	file_val.open(finputName);

	string input;
	string command;

	int degree = 0;
	//int *level;
	vector<int> level;
	int ct = 0;
	bool travarse = false;

	while (getline(file_cmd, command, '\n'))                        //command
	{
		//cout << command << endl;

		int find_deg = command.find("Degree=");
		int find_trav = command.find("Inorder Traversal");
		int find_lev = command.find("Level");
		if (find_deg == 0)
		{
			std::string substr = command.substr(7, sizeof(command)-7);
			degree = atoi(substr.c_str());
			cout << "Degree aru" <<degree<< endl;
			find_deg = -1;
		}
		else if (find_trav == 0)
		{
			travarse = true;
			cout << "Nrrd trav "<< endl;

			find_trav = -1;
			//cout << "Inorder Traversal aru" << endl;
		}
		else if (find_lev == 0)
		{
			//level = new int[20];
			std::string tm = command.substr(6, sizeof(command) - 6);
			level.push_back(atoi(tm.c_str()));
		
			cout << "lev aru" << level.back() << endl;

			find_lev == -1;                                //cout << "Level aru" << endl;
		}
	}

	bTree myTree(degree);

	ofstream y(foutputName);

	while (file_val >> input)                                     // input
	{
		int value = atoi(input.c_str());
		cout << value << endl;

		myTree.insertData(value);

	}
	/*if (input == "") {
		ofstream y(foutputName);
		return 0;
	}*/
	                                                                   // output
	if (travarse)
		myTree.traverse(y);

	for (int i = 0; i < level.size(); i++)
	{
		int lv = level[i];
		myTree.printLev(lv, y);

	}





		//cout <<endl<< "()))))))))))))))))))))))))))))))))" << endl;

		//myTree.print_all_lev();  // this print every level
		//cout << endl << "()))))))))))))))))))))))))))))))))" << endl;

		//myTree.printLev(1);
		//myTree.printLev(2);

		//myTree.printLev(3);

		//myTree.printLev(4);
		//myTree.printLev(6);
		//myTree.printLev(60);


		//cout << endl << "()))))))))))))))))))))))))))))))))" << endl;
		//myTree.traverse();
	y.close();

}

void bTree::printB(node* tp, int level)
{
	int count = 1;
	/*vector<int> kontena;*/

	for (int i = 0; i < tp->data.size(); i++)
	{
		int num = tp->data.at(i);
		
		cout << " level is " << level << " Data : " <<num << endl;
		count += 1;
	}
	
	
	for (int i = 0; i < count ; i++)
	{
		
		if (tp->children.size() != 0)
		{
			printB(tp->children.at(i), level + 1);
		}
	}


}


int bTree::countLev(node*tp, int count)
{
	if (tp->children.size() != 0)
		count += countLev(tp->children.at(0), count);
	
	return count;
}

void bTree::prt_all_lev(node* tp)
{
	int level = countLev(this->root, 1);
	cout << "\n leeeeeeeee vel ha " << level << endl;

	this->kontena.resize(level, vector<int>(0));

	//this->kontena[0].push_back(8);
	//cout << "club 00 " << this->kontena[0][0] << endl;


	just_store(this->root, 0);

	for (int i = 0; i < level; i++)   //print out traversal
	{
		cout << " level : " << i+1 << " -||  ";
		for (int g = 0; g < kontena[i].size(); g++)
		{
			std::cout << kontena[i][g] << " ";
		}
		cout << endl;
	}
	kontena.clear();
}

void bTree::just_store(node* tp, int level)
{
	int count = 1;
	/*vector<int> kontena;*/

	for (int i = 0; i < tp->data.size(); i++)
	{
		int num = tp->data.at(i);

		this->kontena[level].push_back(num);
		//cout << " level is " << level << " Data : " << num << endl;
		count += 1;
	}

	for (int i = 0; i < count; i++)
	{

		if (tp->children.size() != 0)
		{
			just_store(tp->children.at(i), level + 1);
		}
	}

}

void bTree::prt_a_lev(node* tp, int levelNum, ofstream& y)   // levelNUm is specific level that wanted to print
{
	int level = countLev(this->root, 1);
	cout << "\n leeeeeeeee vel ha " << level << endl;

	this->kontena.resize(level, vector<int>(0));


	just_store(this->root, 0);

	cout << " level selected is -----------------------" << levelNum << endl;

	if (levelNum > kontena.size())
	{
		cout << "empty" << endl;
		y << "empty" << endl;
		kontena.clear();
		return;
	}


	for (int i = 0; i <kontena[levelNum-1].size(); i++)
	{
		std::cout << kontena[levelNum-1].at(i) << " ";
		y << kontena[levelNum - 1].at(i) << " ";
	}
	cout << endl;
	y << endl;
	//for (int i = 0; i < level; i++)   //print out traversal
	//{
	//	cout << " level : " << i + 1 << " -||  ";
	//	for (int g = 0; g < kontena[i].size(); g++)
	//	{
	//		std::cout << kontena[i][g] << " ";
	//	}
	//	cout << endl;
	//}
	kontena.clear();
	

}

void bTree::print_traverse(node* tp, ofstream& y)
{
	int level = countLev(this->root, 1);
	//cout << "\n leeeeeeeee vel ha " << level << endl;

	this->kontena.resize(level, vector<int>(0));
	
	vector<int> trav(0);                                // to store all datas in kontena
	//this->kontena[0].push_back(8);
	//cout << "club 00 " << this->kontena[0][0] << endl;


	just_store(this->root, 0);
	
	for (int i = 0; i < level; i++)   
	{
		for (int g = 0; g < kontena[i].size(); g++)
		{
			//std::cout << kontena[i][g] << " ";
			trav.push_back(kontena[i][g]) ;

		}
		//cout << endl;
	}

	sort(trav.begin(), trav.end());
	for (int i = 0; i < trav.size(); i++)                         //print out traversal
	{
		//cout << trav[i] << " ";
		y << trav[i] << " ";

	}
	y <<endl;


	kontena.clear();
	

}