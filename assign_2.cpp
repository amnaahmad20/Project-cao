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
//Function to check and return precedence of operators
int prec(char a) {
	if (a == '^')
		return 3;
	else if (a == '/' || a == '*')
		return 2;
	else if (a == '+' || a == '-')
		return 1;
	else
		return -1;
}

// The main function to convert infix expression
//to postfix expression
Stack<char> infixToPostfix(string str) {
	Stack<char> result; //to store result as stack 
	Stack<char> Stack; //For stack operations, we are using our stack class that is mentioned above


	for (int i = 0; i < str.length(); i++) {
		char a = str[i];

		// If the input character is an operand adding it to output string 'result'.
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
			result.push(a);

		// If the character found is an ( its pushed into the stack.
		else if (a == '(')
			Stack.push('(');

		// If the character is an )  pop it and output string from the stack till an ‘(‘ is encountered.
		else if (a == ')') {
			while (Stack.Peak() != '(')
			{
				result.push(' ');
				result.push(Stack.Peak());
				Stack.pop();

			}
			Stack.pop();
		}

		//Working done when an operator is found in the stack
		else {
			result.push(' ');
			while (!Stack.isEmpty() && prec(str[i]) <= prec(Stack.Peak())) {
				result.push(Stack.Peak());
				Stack.pop();

			}
			Stack.push(a); //push the character that is aquired  into stack
		}
	}

	// remaining elements are pop from the stack
	while (!Stack.isEmpty()) {
		result.push(' ');
		result.push(Stack.Peak());
		Stack.pop();

	}

	return result; //printing and returning the postfix string
}
// method for calculating 2 number evaluations
float Evaluate(float a, float b, char o)
{
	switch (o)
	{
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case'^': return pow(a, b);
	}
	return a / b;
}
// method evaluates result of postfix expression
float Result(Stack<char> postfixExpression)
{
	Stack<float> result;
	Stack<char> rev_expression;
	while (!postfixExpression.isEmpty()) // reversing the postfix expression stack for ease
	{
		rev_expression.push(postfixExpression.pop());
	}
	while (!rev_expression.isEmpty()) // iteration done over the stack to check for validaions
	{
		if (isdigit(rev_expression.Peak())) // if entered element is digit using the isdigit
		{
			string char_num = "";
			int place = -1;
			while (rev_expression.Peak() != ' ')
			{
				char_num += rev_expression.pop();
				place++;
			}
			rev_expression.pop();
			float num = 0;
			for (int val = 0; val < char_num.length(); val++) // convert char  to equivalent int dihit for evaluation 
			{
				float x = char_num[val] - '0';
				num += x * pow(10, place);
				place--;
			}
			result.push(num);
		}
		//cheking for the operators
		else if ((rev_expression.Peak() == '+' || rev_expression.Peak() == '-' || rev_expression.Peak() == '*' || rev_expression.Peak() == '/' || rev_expression.Peak() == '^')) // if operator
		{
			// perform specified operation that is written in the expression
			float a = Evaluate(result.pop(), result.pop(), rev_expression.pop());
			// pop back the  result elements into the stack
			result.push(a);
		}
		else
		{
			rev_expression.pop();
		}
	}
	return result.pop(); // return the final result by popping the elements
}
//Main function to test the program
int main() {
	string expression = "";

	cout << "____________Infix to postfix conversion____________" << endl;
	while (true) {
		cout << "Enter any expression to convert it in postfix expression. Press 0 to exit:";
		cin >> expression;
		if (expression == "0")
		{
			cout << "Program ended successfully. Thank you!!" << endl;
			break;
		}
		cout << "postfix expression is:";
		infixToPostfix(expression).display();
		float r = Result(infixToPostfix(expression));
		cout << endl << "result is:" << r << endl;


	}

	return 0;
}

