
#include <iostream>
#include <ctime>
#include <cstdlib>


using namespace std;


struct player {
	int age;
	int number;
	int totalminutes;
	int minutes;
	bool isLocker;
	bool isOnCourt;

	player* next;
	player* prev;

	player()
	{
		number = -1;
		age = -1;
		totalminutes = -1;
		minutes = -1;
		isLocker = true;
		isOnCourt = false;

		next = NULL;
		prev = NULL;

	}

	player(int number, int age, int minutes,int totalminutes, bool isLocker, bool isOnCourt) {
		this->number = number;
		this->age = age;
		this->totalminutes = totalminutes;
		this->minutes = minutes;
		this->isLocker = isLocker;
		this->isOnCourt = isOnCourt;

		next = NULL;
		
		
	}

};

class List {

public:
	player* next; //also head or most left player
	player* prev; //also the tail of the list most right player

	List()
	{
		this->next = NULL;
		this->prev = NULL;

	}

	void add(player* x) {
		if (next == NULL) {
			next = x;
			prev = x;

			return;
		}

		x->prev = prev;
		prev->next = x;
		prev = x;
	}

	void print() {
		player* tmp = next;
		cout << "====== BENCH LIST ======" << endl;
		cout << "   age   ,  no.  , minutes played " << endl;
		while (tmp != NULL) {
			cout << "   " << tmp->age << "   ,  " << tmp->number << "  ,     " << tmp->totalminutes << "     " << endl;
			tmp = tmp->next;
		}
		cout << "======================" << endl;
	}
};

class court {

public:
	int number;
	player* head;
	player* tail;

	court()
	{
		this->head = NULL;
		this->tail = NULL;
	}

	void add(player* x)
	{
		if (head == NULL)
		{
			head = x;
			tail = x;
			return;
		}

		x->prev = tail;  // link the second node back to the first node
		tail->next = x;  // link the first node pointing to the second node
		tail = x;    // tail is still pointing to the first node
                     // so advance tail to the second node
		tail->next = head;
		head->prev = tail;

		++number;
	}

	void print() {

		player* tmp = head;
		player plob;
		cout << "====== COURT LIST ======" << endl;
		cout << "   age   ,  no.  , minutes played " << endl;
		for (int i = 0; i < 5; i++) {			
			cout << "   " << tmp->age << "   ,  " << tmp->number << "  ,     " << tmp->totalminutes << "     " << endl;
			int index = (tmp->number);
			tmp = tmp->next;
		}

		cout << "======================" << endl;

	}

	player* check(int minutes)
	{
		player* tmp = head;
		//player plob;

		for (int i = 0; i < 5; i++) {
			//int index = (tmp->number);

			if (minutes >= tmp->age * 0.1)
			{
				tmp->isOnCourt = true;
				tmp->minutes = minutes;
				return tmp;
			}
			/*else
			{
				tmp->isOnCourt = false;
				tmp->minutes = minutes;
				return false;
			}*/
		
			tmp = tmp->next;
		}
		//cout << "***************" << endl<<endl;

	}
};

class bench
{
private:
	int data;
	player* next;
	player* prev;
};

int main()
{
	srand(time(0));

	court courtLists;
	List bench;

	player locker[12];

	for (int i = 0; i < 12; i++)
	{
		player n = player(i + 1, 17 + (rand() % 38),0,  0, true, false);
		//list.add(n);
		locker[i] = n;
		cout << endl;
	}

	for (int i = 0; i < 5; i++)
	{
		int index = rand() % 11;

		while (locker[index].isLocker != true) {
			index = rand() % 11;
		}
		locker[index].isLocker = false;
		//add player from locker to court
		courtLists.add(&locker[index]);
	}

	for (int i = 0; i < 12; i++) {

		if (locker[i].isLocker == true) {

			locker[i].isLocker = false;
			bench.add(&locker[i]);
		}

	}

	cout << "Beginning court list players" << endl;
	courtLists.print();

	cout << "Beginning bench list players" << endl;
	bench.print();

	cout << "===================================" << endl;

	bool pickLeft = true;
	//player plob;
	for (int minutes = 1; minutes < 49; minutes++) {

		player zeroplayer = player(NULL, 0,0, 0, false, false);
		auto* oldestPlayer = &zeroplayer;

		auto* temp = courtLists.head;

		for (int i = 0; i < 5; i++) {

			if (temp->age > oldestPlayer->age) {			
				oldestPlayer = temp;
			}
			temp = temp->next;
		}

		//courtLists.print();
		//cout << oldestPlayer->age << endl;
	
		auto tempPlayer = courtLists.head;
		for (int i = 0; i < 5; i++) {
			//int index = (tmp->number);
			//auto tmp = courtLists.head;
			tempPlayer->totalminutes = tempPlayer->totalminutes + 1 ;
			tempPlayer->minutes = tempPlayer->minutes + 1;
			tempPlayer = tempPlayer->next;
		}

		//courtLists.print();

		if (oldestPlayer->minutes >= (oldestPlayer->age * 0.1))
		{
			//courtLists.print();
			//bench.print();

			oldestPlayer->minutes = 0;
			oldestPlayer->isOnCourt = false;

			auto* currentPlayer = oldestPlayer;
			auto* currentplayerPrevious = oldestPlayer->prev;
			auto* currentplayerNext = oldestPlayer->next;

			auto* firstBenchonLeft = bench.next;
			auto* secondBenchonLeft = bench.next->next;
			auto* thirdBenchonLeft = secondBenchonLeft->next;

			auto* firstBenchonRight = bench.prev;
			auto* secondBenchonRight = bench.prev->prev;
			auto* thirdBenchonRight = secondBenchonRight->prev;

			if (pickLeft == true) {
				//courtLists.print();
				//bench.print();
				int currentQuarter = (minutes / 12);
				cout << "Replacement Player, " << "Replacing, " << "Replacement time in the Quarter & Minutes " << endl;
				cout << oldestPlayer->number << "            " << secondBenchonLeft->number << "      Q:" << currentQuarter << " Minute: " << minutes << endl;

				oldestPlayer->prev = NULL;
				bench.next = currentPlayer;

				firstBenchonLeft->prev = oldestPlayer;
				oldestPlayer->next = firstBenchonLeft;

				thirdBenchonLeft->prev = firstBenchonLeft;
				firstBenchonLeft->next = thirdBenchonLeft;

				secondBenchonLeft->prev = currentplayerPrevious;
				currentplayerPrevious->next = secondBenchonLeft;
				secondBenchonLeft->next = currentplayerNext;
				currentplayerNext->prev = secondBenchonLeft;

				if (courtLists.head == currentPlayer) {
					courtLists.head = secondBenchonLeft;
					courtLists.head->prev = currentplayerPrevious;
					courtLists.head->next = currentplayerNext;
				}
				else if (courtLists.tail == currentPlayer) {
					courtLists.tail = secondBenchonLeft;
					courtLists.tail->prev = currentplayerPrevious;
					courtLists.tail->next = currentplayerNext;
				}
				pickLeft = false;
			}
			else if (pickLeft == false){
				//courtLists.print();
				//bench.print();
				int currentQuarter = (minutes / 12);
				cout << "Replacement Player, " << "Replacing, " << "Replacement time in the Quarter & Minutes " << endl;
				cout << oldestPlayer->number << "            " << secondBenchonRight->number << "      Q:" << currentQuarter << " Minute: " << minutes << endl;

				oldestPlayer->next = NULL;
				bench.prev = currentPlayer;

				firstBenchonRight->next = oldestPlayer;
				oldestPlayer->prev = firstBenchonRight;

				thirdBenchonRight->next = firstBenchonRight;
				firstBenchonRight->prev = thirdBenchonRight;

				secondBenchonRight->prev = currentplayerPrevious;
				currentplayerPrevious->next = secondBenchonRight;
				secondBenchonRight->next = currentplayerNext;
				currentplayerNext->prev = secondBenchonRight;

				if (courtLists.head == currentPlayer) {
					courtLists.head = secondBenchonRight;
					courtLists.head->prev = currentplayerPrevious;
					courtLists.head->next = currentplayerNext;
				}
				else if (courtLists.tail == currentPlayer) {
					courtLists.tail = secondBenchonRight;
					courtLists.tail->prev = currentplayerPrevious;
					courtLists.tail->next = currentplayerNext;
				};
				pickLeft = true;
			
			}
			//cout << courtLists.head->age << endl;
			//cout << bench.next->age << endl;
		}
		
		//courtLists.print();
		//bench.print();

		//cout << "" << endl;
		//print report every 12 minutes
		if (minutes % 12 == 0) {

			int currentQuarter = (minutes / 12);
			cout << " current Quarter: " << currentQuarter << endl;
			cout << "====================" << endl;
			courtLists.print();
			bench.print();
		}
		//this is picking player from the bench
		//if (pickLeft == true) {
		//	auto current = bench.next;
		//	while (current->prev != NULL) {
		//		current = current->prev;
		//	}
		//}
		

	}
	system("pause");
}
