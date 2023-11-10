#include <iostream>
#include <string>

#define STD 1

#if STD
# define NAMESPACE ft
	#include <stack>
	#include "headers/utils/colors.hpp"
	namespace ft = std;
#else
	# define NAMESPACE std
	#include "headers/stack.hpp"
	#include "headers/utils/colors.hpp"
#endif

using namespace NAMESPACE;

void 	print_sep(void) 
{
	cout << CYN << "+";
	for (int i = 0; i < 50; i++) {
		if (i % 2 == 0)
			cout << BGRN << "-";
		else
			cout << BRW << "-";
	}
	cout << CYN << "+" << NC << std::endl;
}

void    print_stack(ft::stack<int> stack, bool printOrNot)
{
	if (printOrNot)
		std::cout << HPUR << "My stack contains: " << NC << std::endl;
	while (stack.size() > 0)
	{
		cout << stack.top() << " ";
		stack.pop();
	}
	cout << std::endl;
	if (printOrNot)
	{
		cout << CYN << "+";
		for (int i = 0; i < 50; i++) {
			if (i % 2 == 0)
				cout << BGRN << "-";
			else
				cout << BRW << "-";
		}
		cout << CYN << "+" << NC << std::endl;
	}
}

int main(void)
{
	ft::stack<int> stack;
	// EMPTY
	cout << URED << "EMPTY" << NC << endl;
	cout << GR << "Check if empty" << NC << endl;
	if (stack.empty())
		cout << "Stack is empty" << endl;
	else
		cout << "Stack is not empty" << endl;
	print_sep();
	// INSERT
	cout << URED << "INSERT" << NC << endl;
	cout << GR << "Insert 10 elements" << NC << endl;
	for (int i = 0; i < 20; i++)
		stack.push(i);
	print_stack(stack, true);

	cout << GR << "Insert 10 elements" << NC << endl;
	for (int i = 100; i < 110; i++)
		stack.push(i);
	print_stack(stack, true);

	// EMPTY
	cout << URED << "EMPTY" << NC << endl;
	cout << GR << "Check if empty" << NC << endl;
	if (stack.empty())
		cout << "Stack is empty" << endl;
	else
		cout << "Stack is not empty" << endl;
	print_sep();

	// SIZE
	cout << URED << "SIZE" << NC << endl;
	cout << GR << "Check size" << NC << endl;
	cout << "Size is " << stack.size() << endl;
	print_sep();

	// TOP
	cout << URED << "TOP" << NC << endl;
	cout << GR << "Check top" << NC << endl;
	cout << "Top is " << stack.top() << endl;
	print_sep();

	// POP
	cout << URED << "POP" << NC << endl;
	cout << GR << "Pop 5 elements" << NC << endl;
	for (int i = 0; i < 5; i++)
		stack.pop();
	print_stack(stack, true);

	// RELATIONAL OPERATORS
	cout << URED << "RELATIONAL OPERATORS" << NC << endl;
	cout << GR << "Create a new stack" << NC << endl;
	ft::stack<int> stack2;
	for (int i = 1000; i < 1010; i++)
		stack2.push(i);
	cout << HPUR << "My second stack contains: " << NC << endl;
	print_stack(stack2, false);
	cout << HPUR << "My first stack contains: " << NC << endl;
	print_stack(stack, false);
	cout << GR << "Check if stack is equal to stack2" << NC << endl;
	if (stack == stack2)
		cout << "Stack is equal to stack2" << endl;
	else
		cout << "Stack is not equal to stack2" << endl;
	cout << GR << "Check if stack is smaller than stack2" << NC << endl;
	if (stack < stack2)
		cout << "Stack is smaller than stack2" << endl;
	else
		cout << "Stack is not smaller than stack2" << endl;
	cout << GR << "Check if stack is greater than stack2" << NC << endl;
	if (stack > stack2)
		cout << "Stack is greater than stack2" << endl;
	else
		cout << "Stack is not greater than stack2" << endl;
	print_sep();

	// OPERATOR =
	cout << URED << "OPERATOR =" << NC << endl;
	cout << GR << "Assign stack2 to stack" << NC << endl;
	cout << GR << "Before assignation: " << NC << endl;
	print_stack(stack, false);
	stack = stack2;
	print_stack(stack, true);
	return (0);
}