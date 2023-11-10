#include <iostream>
#include <string>

#define STD 1

#if STD
# define NAMESPACE ft
	#include <vector>
	#include "headers/utils/colors.hpp"
	namespace ft = std;
#else
	# define NAMESPACE std
	#include "headers/vector.hpp"
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

void    print_vector(ft::vector<int> v, bool printOrNot)
{
	if (printOrNot)
		std::cout << HPUR << "My vector contains: " << NC << std::endl;
	for (ft::vector<int>::iterator it = v.begin(); it != v.end(); it++)
		cout << *it << " ";
	if (v.size() == 0)
		cout << "NOTHING !";
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

int main()
{
	// INSERT
	cout << URED << "INSERT" << NC << endl;
	cout << GR << "Insert 10 elements" << NC << endl;
	ft::vector<int> v;
	for (int i = 10; i < 50; i++)
		v.push_back(i);
	print_vector(v, true);
	cout << GR << "Insert 10 elements at the beginning" << NC << endl;
	for (int i = 9; i > 0; i--)
		v.insert(v.begin(), i);
	print_vector(v, true);
	cout << GR << "Insert 10 elements at the end" << NC << endl;
	for (int i = 50; i < 60; i++)
		v.insert(v.end(), i);
	print_vector(v, true);
	cout << GR << "Insert 1 elements at the middle" << NC << endl;
		v.insert(v.begin() + 10, 123233);
	print_vector(v, true);
	cout << GR << "Insert range of elements at the middle" << NC << endl;
	ft::vector<int> v2;
	for (int i = 1000; i < 1010; i++)
		v2.push_back(i);
	v.insert(v.begin() + 10, v2.begin(), v2.end());
	print_vector(v, true);
	
	// PUSH_BACK
	cout << URED << "\nPUSH_BACK" << NC << endl;
	cout << GR << "Push 1 element" << NC << endl;
	v.push_back(3942);
	print_vector(v, true);

	//BEGIN
	cout << URED << "\nBEGIN" << NC << endl;
	cout << GR << "Print first element" << NC << endl;
	cout << "First element is : " << *v.begin() << std::endl;
	print_sep();
	//END
	cout << URED << "\nEND" << NC << endl;
	cout << GR << "Print last element" << NC << endl;
	cout << "Last element is : " << *(v.end() - 1) << std::endl;
	print_sep();

	// REND
	cout << URED << "\nREND" << NC << endl;
	cout << GR << "Print first element" << NC << endl;
	cout << "First element is : " << *v.rbegin() << std::endl;
	print_sep();

	// RBEGIN
	cout << URED << "\nRBEGIN" << NC << endl;
	cout << GR << "Print last element" << NC << endl;
	cout << "Last element is : " << *(v.rend() - 1) << std::endl;
	print_sep();

	// POP_BACK
	cout << URED << "\nPOP_BACK" << NC << endl;
	cout << GR << "Pop 1 element : " << *(v.end() - 1) << NC << endl;
	v.pop_back();
	print_vector(v, true);


	// ERASE
	cout << URED << "\nERASE" << NC << endl;
	cout << GR << "Erase 10 elements at the beginning" << NC << endl;
	for (int i = 0; i < 10; i++)
		v.erase(v.begin());
	print_vector(v, true);
	cout << GR << "Erase 10 elements at the end" << NC << endl;
	for (int i = 0; i < 10; i++)
		v.erase(v.end() - 1);
	print_vector(v, true);
	cout << GR << "Erase 1 elements at the middle" << NC << endl;
	cout << "Element that we're going to destroy is : " << v.at(10) << std::endl;
	v.erase(v.begin() + 10);
	print_vector(v, true);
	cout << GR << "Erase range of elements at the middle" << NC << endl;
	v.erase(v.begin() + 10, v.begin() + 20);
	print_vector(v, true);

	// SWAP
	cout << URED << "\nSWAP" << NC << endl;
	cout << GR << "Swap 2 vectors" << NC << endl;
	ft::vector<int> v3;
	for (int i = 100; i < 110; i++)
		v3.push_back(i);
	v.swap(v3);
	cout << ORA << "V contains now: " << NC << std::endl;
	print_vector(v, false);
	cout << ORA << "V3 contains now: " << NC << std::endl;
	print_vector(v3, false);
	print_sep();

	// CLEAR
	cout << URED << "\nCLEAR" << NC << endl;
	v.clear();
	print_vector(v, true);

	// RESIZE
	cout << URED << "\nRESIZE" << NC << endl;
	cout << GR << "Resize 10 elements" << NC << endl;
	v.resize(10);
	print_vector(v, true);

	// ASSIGN
	cout << URED << "\nASSIGN" << NC << endl;
	cout << GR << "Assign 10 elements" << NC << endl;
	v.assign(10, 123);
	print_vector(v, true);

	// RESERVE
	cout << URED << "\nRESERVE" << NC << endl;
	cout << GR << "Reserve 100 elements" << NC << endl;
	v.reserve(100);
	cout << "Capacity: " << v.capacity() << std::endl;
	print_vector(v, true);

	// RELATIONAL OPERATORS
	cout << URED << "\nRELATIONAL OPERATORS" << NC << endl;
	cout << GR << "Relational operators" << NC << endl;
	ft::vector<int> v4;
	for (int i = 0; i < 10; i++)
		v4.push_back(i);
	ft::vector<int> v5;
	for (int i = 10; i < 20; i++)
		v5.push_back(i);
	cout << HPUR << "v4 contains: " << NC << std::endl;
	print_vector(v4, false);
	cout << HPUR << "v5 contains: " << NC << std::endl;
	print_vector(v5, false);
	if (v4 == v5)
		cout << "v4 == v5" << std::endl;
	else if (v4 != v5)
		cout << "v4 != v5" << std::endl;
	if (v4 < v5)
		cout << "v4 < v5" << std::endl;
	else if (v4 > v5)
		cout << "v4 > v5" << std::endl;
	if (v4 <= v5)
		cout << "v4 <= v5" << std::endl;
	else if (v4 >= v5)
		cout << "v4 >= v5" << std::endl;
	
	print_sep();
	// OPERATOR[]
	cout << URED << "\nOPERATOR[]" << NC << endl;
	cout << GR << "Operator[]" << NC << endl;
	ft::vector<int> v6;
	for (int i = 0; i < 10; i++)
		v6.push_back(i);
	cout << HPUR << "v6 contains: " << NC << std::endl;
	print_vector(v6, false);
	cout << "v[5] = " << v6[5] << std::endl;
	v6[5] = 123;
	cout << "v[5] = " << v6[5] << std::endl;
	cout << "v[122] = " << v6[122] << std::endl;

	// CONSTRUCTORS COPY
	cout << URED << "\nCONSTRUCTORS COPY" << NC << endl;
	cout << GR << "Copy constructor" << NC << endl;
	cout << HPUR << "v6 contains: " << NC << std::endl;
	print_vector(v6, false);
	ft::vector<int> v7(v6);
	print_vector(v7, true);

	// CONSTRUCTORS RANGE
	cout << URED << "\nCONSTRUCTORS RANGE" << NC << endl;
	cout << GR << "Range constructor" << NC << endl;
	cout << HPUR << "v6 contains: " << NC << std::endl;
	print_vector(v6, false);
	ft::vector<int> v8(v6.begin() + 2, v6.end());
	print_vector(v8, true);

	// CONSTRUCTORS FILL
	cout << URED << "\nCONSTRUCTORS FILL" << NC << endl;
	cout << GR << "Fill constructor" << NC << endl;
	ft::vector<int> v9(10, 42);
	print_vector(v9, true);

	// CONSTRUCTORS DEFAULT
	cout << URED << "\nCONSTRUCTORS DEFAULT" << NC << endl;
	cout << GR << "Default constructor" << NC << endl;
	ft::vector<int> v10;
	print_vector(v10, true);
	return (0);
}