// By Edward Burke 
// 001602259 

#include <iostream>
#include <stack>

using namespace std;

// Stack implementation, taken from lecture notes 
template<class ItemType>
class ArrayStack {
private:
	static const int DEFAULT_CAPACITY = 50;
	ItemType items[DEFAULT_CAPACITY];
	int top;

public: 
	ArrayStack();
	bool isEmpty() const;
	bool push(const ItemType& newEntry);
	bool pop();
	ItemType peek() const;
};

template<class ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1) {}

template<class ItemType>
bool ArrayStack<ItemType>::isEmpty() const {
	return top < 0;
}

template<class ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry) {
	bool result = false;
	if (top < DEFAULT_CAPACITY - 1) {
		top++;
		items[top] = newEntry;
		result = true;
	}
	return result;
}

template<class ItemType>
bool ArrayStack<ItemType>::pop() {
	bool result = false;
	if (!isEmpty()) {
		top--;
		result = true;
	}
	return result;
}

template<class ItemType>
ItemType ArrayStack<ItemType>::peek() const {
	// I was having trouble with assert not working, so I had to remove it and was just careful with my stack calls 
	//assert(!isEmpty());
	return items[top];
}

// Contains a decimal number and converts it to binary 
class Dec2Bin {
public:
	// Decimal number to be converted to binary 
	int decNum;
	Dec2Bin() : decNum(0) {};
	void readDecNum() {
		cout << "What is the decimal number? ";
		cin >> decNum;
	}
	// Converts decimal to binary recursivly 
	void dec2bin_rcv(int d) {
		// If d = 0 or 1, those are the same in binary, so print them 
		if (d <= 1) {
			cout << d;
		}
		// Otherwise, return the modulo of it and bitshift it away 
		else {
			dec2bin_rcv(d >> 1);
			cout << d % 2;
		}

	}
	// Converts decimal to binary iterivly 
	void dec2bin_itr() {
		ArrayStack<int> stack;
		int len = 0;
		while (decNum > 1) {
			stack.push(decNum % 2);
			len += 1;
			decNum >>= 1;
		}
		stack.push(decNum);
		len += 1;
		for (int i = 0; i < len; i++) {
			cout << stack.peek();
			stack.pop();
		}
	}
		// Stackless implementation I made before I realized I had to use the stack 
		// Saw no reason to delete it 
		/*while (decNum > 1) {
			cout << decNum % 2;
			decNum >>= 1;
		}
		// Once the loop is done, add the final remaining value 
		cout << decNum;
	}*/
};

int F1(int n) {
	if (n == 0) {
		return 1;
	}
	if (n % 2 == 0) {
		int result = F1(n / 2);
		return result * result;
	}
	else {
		return 2 * F1(n - 1);
	}
}

int F2(int n) {
	if (n == 0) {
		return 1;
	}
	return 2 * F2(n - 1);
}

int F3(int n) {
	if (n == 0) {
		return 1;
	}
	return F3(n - 1) + F3(n - 1);
}

// Gets the fibonacci digit of n without dynamic programming 
int fibRecur(int n) {
	// fib(0) and fib(1) are 0 and 1 
	if (n < 2) {
		return n;
	}
	// Sums the two previous fibs 
	return fibRecur(n - 1) + fibRecur(n - 2);
}

// Global array for dynamic programming 
// 40 is the max length we should need, but make this longer for longer n values 
int fibList[40];

// Resets FibList 
void resetFibList() {
	for (int i = 0; i < 40; i++) {
		fibList[i] = -1;
	}
}

// Finds the fibonacci digit of n with dynamic programming 
int fibDynamic(int n) {
	// Value of fib(n - 1)
	int min1;
	// Value of fib(n - 2) 
	int min2;
	// Base case 
	if (n < 2) {
		return n;
	}
	// Gets the value of min1 from fibList, or calculates and stores it if needed 
	if (fibList[n - 1] == -1) {
		min1 = fibDynamic(n - 1);
		fibList[n - 1] = min1;
	}
	else {
		min1 = fibList[n - 1];
	}
	// Gets the value of min2 from fibList, or calculates and stores it if needed 
	if (fibList[n - 2] == -1) {
		min2 = fibDynamic(n - 2);
		fibList[n - 2] = min2;
	}
	else {
		min2 = fibList[n - 2];
	}
	return min1 + min2;
}

int main() {
	// Test code for Dec2Bin (taken from assignment) 
	cout << "Testing Problem 1:\n";
	Dec2Bin db;
	db.readDecNum();
	cout << "The binary nuumber using recursive method = ";
	db.dec2bin_rcv(db.decNum);
	cout << "\nThe binary number using iterative method = ";
	db.dec2bin_itr();

	// Test code for F1, F2, F3 (written by me) 
	cout << "\n\nTesting Problem 2:\n";
	cout << "F1:\n";
	cout << F1(1) << "\n";
	cout << F1(3) << "\n";
	cout << F1(5) << "\n";
	cout << F1(16) << "\n";
	cout << F1(24) << "\n";
	cout << F1(26) << "\n";
	cout << F1(30) << "\n";
	cout << "\nF2:\n";
	cout << F2(1) << "\n";
	cout << F2(3) << "\n";
	cout << F2(5) << "\n";
	cout << F2(16) << "\n";
	cout << F2(24) << "\n";
	cout << F2(26) << "\n";
	cout << F2(30) << "\n";
	cout << "\nF3:\n";
	// May want to comment out the F3 commands to run output faster 
	cout << F3(1) << "\n";
	cout << F3(3) << "\n";
	cout << F3(5) << "\n";
	cout << F3(16) << "\n";
	cout << F3(24) << "\n";
	cout << F3(26) << "\n";
	cout << F3(30) << "\n";

	// Fibonacci tests 
	cout << "\nTesting Problem 3:\n";
	cout << "Without Dynamic Programming:\n";
	cout << fibRecur(5) << "\n";
	cout << fibRecur(10) << "\n";
	cout << fibRecur(20) << "\n";
	cout << fibRecur(30) << "\n";
	cout << fibRecur(40) << "\n";
	cout << "With Dynamic Programming:\n";
	// Resets fibList between runs 
	resetFibList();
	cout << fibDynamic(5) << "\n";
	resetFibList();
	cout << fibDynamic(10) << "\n";
	resetFibList();
	cout << fibDynamic(20) << "\n";
	resetFibList();
	cout << fibDynamic(30) << "\n";
	resetFibList();
	cout << fibDynamic(40) << "\n";
	return 0;
}
