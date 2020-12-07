/* The group assignment contains ADT's for SortedArray, UnsortedArray, and HashTable
 - Used to compare the execution times between each ADT for insert, remove, and search.
 - By Justin Santos, Karla Lemus, and Aiden Takei.
*/


#include <iostream>
#include <chrono>
using namespace std;

template <class T>
class SortedArray
{
private:
	int maxSize;
	int currSize;
	T* arr;
public:
	SortedArray(int size = 100)
	{
		if (size <= 0)
			size = 10;

		maxSize = size;
		currSize = 0;
		arr = new T[size];
	}
	bool isEmpty()
	{
		return currSize == 0;
	}
	bool isFull()
	{
		return currSize == maxSize;
	}
	void insert(T var)
	{
		// Do nothing if array is full. Just set it if array is empty.
		if (isFull())
			return;
		else if (isEmpty())
		{
			arr[0] = var;
			currSize += 1;
			return;
		}

		int i = currSize - 1;
		while ((i >= 0) && (arr[i] > var))
		{
			arr[i + 1] = arr[i];
			i--;
		}

		arr[i + 1] = var;
		currSize += 1;
	}
	void remove(T var)
	{
		// Do nothing if array is empty.
		if (isEmpty())
			return;

		// Do nothing if var doesn't exist in array.
		int index = binarySearch(var);
		if (index == -1)
			return;

		for (int i = index; i < currSize; i++)
			arr[i] = arr[i + 1];

		currSize -= 1;
	}
	// Overloaded binarySearch function to be used initially.
	int binarySearch(T var) {
		int p = 0;
		int r = currSize - 1;

		if (p <= r) {
			int mid = (p + r) / 2;
			if (arr[mid] == var)
				return mid;
			if (arr[mid] > var)
				return binarySearch(var, p, mid - 1);
			if (arr[mid] < var)
				return binarySearch(var, mid + 1, r);
		}
		return -1;
	}
	// Binary search function used to find the index of a given value. Returns -1 otherwise.
	int binarySearch(T var, int p, int r) {
		if (p <= r) {
			int mid = (p + r) / 2;
			if (arr[mid] == var)
				return mid;
			if (arr[mid] > var)
				return binarySearch(var, p, mid - 1);
			if (arr[mid] < var)
				return binarySearch(var, mid + 1, r);
		}
		return -1;
	}
	void print()
	{
		for (int i = 0; i < currSize; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
};

template <class T>
class UnsortedArray
{
private:
	int maxSize;
	int currSize;
	T* arr;
public:
	UnsortedArray(int size)
	{
		if (size <= 0)
			size = 10;

		maxSize = size;
		currSize = 0;
		arr = new T[size];
	}
	bool isEmpty()
	{
		return currSize == 0;
	}
	bool isFull()
	{
		return currSize == maxSize;
	}
	void insert(T var)
	{
		// Do nothing if array is full. Just set it if array is empty.
		if (isFull())
			return;

		arr[currSize] = var;
		currSize += 1;
	}
	void remove(T var)
	{
		// Do nothing if array is empty.
		if (isEmpty())
			return;

		// Do nothing if var doesn't exist in array.
		int index = linearSearch(var);
		if (index == -1)
			return;

		for (int i = index; i < currSize; i++)
			arr[i] = arr[i + 1];

		currSize -= 1;
	}
	// Uses linear search to return index of given value. Returns -1 otherwise.
	int linearSearch(T var)
	{
		for (int i = 0; i < currSize; i++)
			if (arr[i] == var)
				return i;
		return -1;
	}
	void print()
	{
		for (int i = 0; i < currSize; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
};

template <class T>
class hashT
{
private:
	T* HTable;   //pointer to the hash table
	int* indexStatusList;  //pointer to the array indicating the status of a position in the hash table
	int length;    //number of items in the hash table
	int HTSize;    //maximum size of the hash table
public:
	hashT(int size = 100)
	{
		if (size <= 0)
			size = 100;

		HTable = new T[size];
		indexStatusList = new int[size];
		length = 0;
		HTSize = size;

		for (int i = 0; i < HTSize; i++)
		{
			HTable[i] = NULL;
			indexStatusList[i] = NULL;
		}
	}
	~hashT()
	{
		delete[] HTable;
		delete[] indexStatusList;
	}
	int hashFunc(int hashIndex) const
	{
		return hashIndex % HTSize;
	}
	// Function used to insert variable rec based on hashIndex.
	void insert(int hashIndex, const T& rec)
	{
		if (isFull())
			return;

		// Finds an empty index using hashFunc.
		int index = hashFunc(hashIndex);
		while (HTable[index] != NULL && indexStatusList[index] != hashIndex)
			index = hashFunc(index + 1);

		// Checks whether it is an empty index or the correct hashIndex.
		if (HTable[index] == NULL)
			indexStatusList[index] = hashIndex;

		HTable[index] = rec;
		length += 1;
	}
	// Searches the function for a specific rec, starting at hashIndex 
	// Function will look through the whole array if hashIndex is incorrect.
	// Sets found to true/false depending on if it is found.
	// Returns the index of the array where the variable rec is found.
	int search(int hashIndex, const T& rec, bool& found)
	{
		int timeout = 0;
		int index = hashFunc(hashIndex);
		while (HTable[index] != rec && timeout < HTSize)
		{
			index = hashFunc(index + 1);
			timeout += 1;
		}
		if (timeout >= HTSize)
		{
			found = false;
			return -1;
		}

		found = true;
		return index;
	}
	// Checks whether the hash location and it's data is corresponds to hashIndex and rec.
	bool isItemAtEqual(int hashIndex, const T& rec) const
	{
		int timeout = 0;
		int index = hashFunc(hashIndex);
		while (HTable[index] != NULL && indexStatusList[index] != hashIndex && timeout < HTSize)
		{
			index = hashFunc(index + 1);
			timeout += 1;
		}
		if (HTable[index] == NULL || HTable[index] != rec)
			return false;

		return true;
	}
	bool isFull() const
	{
		return length == HTSize;
	}
	// Function used to retrieve from a specific hash.
	void retrieve(int hashIndex, T& rec) const
	{
		// Finds the specific value within array based on hashIndex.
		int index = hashFunc(hashIndex);
		while (HTable[index] != NULL && indexStatusList[index] != hashIndex)
			index = hashFunc(index + 1);

		// If found, sets variable rec to value found within array.
		if (HTable[index] != NULL)
			rec = HTable[index];
	}
	// Function used to remove from a specific hash.
	void remove(int hashIndex, T& rec)
	{
		// Finds the specific value within array based on hashIndex.
		int index = hashFunc(hashIndex);
		while (HTable[index] != NULL && indexStatusList[index] != hashIndex)
			index = hashFunc(index + 1);

		// If value not found, exits function.
		if (HTable[index] == NULL)
			return;

		// Sets variable rec to value found within array then clears position.
		rec = HTable[index];
		HTable[index] = NULL;
		indexStatusList[index] = NULL;
		length -= 1;
	}
	void print() const
	{
		for (int i = 0; i < HTSize; i++)
			if (HTable[i] != NULL)
				cout << HTable[i] << " ";
		cout << endl;
	}
};

double returnInSeconds(chrono::steady_clock::time_point start, chrono::steady_clock::time_point stop)
{
	return (double)(stop - start).count() / 1000000000;
}

int main()
{
	int arr[] = { 28, 51, 11, 2, 94, 96, 2, 86, 30, 21, 59, 29, 54, 63, 18, 100, 35, 87, 60, 19 };
	int arrSize = 20;
	int temp;
	bool bTemp;
	chrono::steady_clock::time_point start, stop;

	SortedArray<int>* var1 = new SortedArray<int>(arrSize);
	UnsortedArray<int>* var2 = new UnsortedArray<int>(arrSize);
	hashT<int>* var3 = new hashT<int>(arrSize);

	cout << "Inserting Integers: " << endl;
	// Inserting all 20 integers into each ADT's
	// Sorted Array
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < arrSize; i++)
		var1->insert(arr[i]);
	stop = chrono::high_resolution_clock::now();
	cout << "Sorted Array: " << returnInSeconds(start, stop) << endl;

	// Unsorted Array
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < arrSize; i++)
		var2->insert(arr[i]);
	stop = chrono::high_resolution_clock::now();
	cout << "Unsorted Array: " << returnInSeconds(start, stop) << endl;

	// HashTable
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < arrSize; i++)
		var3->insert(arr[i], arr[i]);
	stop = chrono::high_resolution_clock::now();
	cout << "HashTable: " << returnInSeconds(start, stop) << endl;


	cout << "\nDeleting Integers: " << endl;
	// Deleting all 20 integers for each ADT
	// Sorted Array
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < arrSize; i++)
		var1->remove(arr[i]);
	stop = chrono::high_resolution_clock::now();
	cout << "Sorted Array: " << returnInSeconds(start, stop) << endl;

	// Unsorted Array
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < arrSize; i++)
		var2->remove(arr[i]);
	stop = chrono::high_resolution_clock::now();
	cout << "Unsorted Array: " << returnInSeconds(start, stop) << endl;

	// HashTable
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < arrSize; i++)
		var3->remove(arr[i], temp);
	stop = chrono::high_resolution_clock::now();
	cout << "HashTable: " << returnInSeconds(start, stop) << endl;


	cout << "\nSearching: " << endl;
	// Searching all 20 integers for each ADT
	// Sorted Array
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < arrSize; i++)
		var1->binarySearch(arr[i]);
	stop = chrono::high_resolution_clock::now();
	cout << "Sorted Array: " << returnInSeconds(start, stop) << endl;

	// Unsorted Array
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < arrSize; i++)
		var2->linearSearch(arr[i]);
	stop = chrono::high_resolution_clock::now();
	cout << "Unsorted Array: " << returnInSeconds(start, stop) << endl;

	// HashTable
	start = chrono::high_resolution_clock::now();
	for (int i = 0; i < arrSize; i++)
		var3->search(arr[i], arr[i], bTemp);
	stop = chrono::high_resolution_clock::now();
	cout << "HashTable: " << returnInSeconds(start, stop) << endl;
}
