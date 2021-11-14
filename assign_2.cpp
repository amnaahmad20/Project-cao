#include<iostream>
#include<string>
#include<cmath>// including cmath for calculation purposes and result findings
using namespace std;
//implementation of  stack class 'Stack'
template <typename t>
class Stack
{
private: // access modifier decleration
	 // pointer stores address of the created array
	t *myarray;
	// variables that contain total storage of array and total number of elements in the array
	int storage, ele;

	// function decreases capacity of the array 
	void shrink()
	{
		ele -= 1;
		t *new_array = new t[ele];
		storage = ele;
		// moves element occurance to new array
		for (int index = 0; index < ele; index++)
		{
			new_array[index] = myarray[index];
		}
		// deletez the old array 
		delete[] myarray;
		// assignment of new array to the pointer variable
		myarray = new_array;
	}
	// function to increase storage and capacity of array 
	void grow()
	{
		// cout << storage << ele << endl;
		// storage doubles similar to vector class
		storage += 1;
		// creation of new array
		t *new_array = new t[storage];
		for (int val = 0; val < (storage - 1); val++) // transfer ele to new array
		{
			new_array[val] = myarray[val];
		}
		delete[] myarray;    // for deletion of previous array
		// assigns new array to the pointer
		myarray = new_array;
	}

public:
	Stack()
	{ // default constructor made here
		myarray = new t[10];
		storage = 1;
		ele = 0;
	}

	// check applied to test that stack is isEmpty or not
	bool isEmpty()
	{
		if (storage == 0)
		{
			return true;
		}
		return false;
	}

	// inserts new  element at Peak of stack
	void push(t value)
	{
		if (storage == ele) // check whether array is full or spaced
		{
			grow(); // increase storage of array if array is full
		}
		myarray[ele] = value; // add new data to the array 
		ele += 1;
	}

	// pop element at Peak of stack using array 
	t pop()
	{
		if (!isEmpty())
		{
			t popped = myarray[ele - 1];
			shrink();
			return popped;
		}
		return '0';
	}

	// display the value stored in the element at peak place
	t Peak()
	{
		if (!isEmpty())
		{
			return myarray[ele - 1];
		}
		return '0';
	}

	// release the memory used and required by stack
	void clear()
	{
		delete[] myarray;
	}

	// function to get size of stack implemented
	int getSize()
	{
		return storage;
	}

	void display()//display function 
	{
		for (int i = 0; i < ele; i++)
		{
			cout << myarray[i];
		}
		cout << endl;
	}
};