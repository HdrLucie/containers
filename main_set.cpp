#include <iostream>
#include <string>

#define STD 0

#if STD
# define NAMESPACE ft
	#include <set>
	#include "headers/utils/colors.hpp"
	namespace ft = std;
#else
	# define NAMESPACE std
	#include "headers/set.hpp"
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

void	printset(ft::set<int> set, bool printOrNot) 
{
	if (printOrNot)
		std::cout << HPUR << "My set contains: " << NC << std::endl;
	for (ft::set<int>::iterator it = set.begin(); it != set.end(); it++)
		std::cout << *it << std::endl;
	if (set.size() == 0)
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

int main(void)
{
	ft::set<int> set;

	// EMPTY
	cout << URED << "EMPTY" << NC << endl;
	cout << GR << "Check if empty" << NC << endl;
	if (set.empty())
		cout << "set is empty" << endl;
	else
		cout << "set is not empty" << endl;
	print_sep();

	// INSERT
	cout << URED << "INSERT" << NC << endl;
	cout << GR << "Inserting 1, 2, 3, 4, 5" << NC << endl;
	for (int i = 1; i <= 5; i++)
		set.insert(i);
	printset(set, true);

	// EMPTY
	cout << URED << "EMPTY" << NC << endl;
	cout << GR << "Check if empty" << NC << endl;
	if (set.empty())
		cout << "set is empty" << endl;
	else
		cout << "set is not empty" << endl;
	print_sep();

	// SIZE
	cout << URED << "SIZE" << NC << endl;
	cout << GR << "Size of set" << NC << endl;
	cout << "Size of set is " << set.size() << endl;
	print_sep();

	// MAX_SIZE
	cout << URED << "MAX_SIZE" << NC << endl;
	cout << GR << "Max size of set" << NC << endl;
	cout << "Max size of set is " << set.max_size() << endl;
	print_sep();

	// INSERT
	cout << URED << "INSERT" << NC << endl;
	cout << GR << "Inserting 6, 7, 8, 9, 10" << NC << endl;
	for (int i = 6; i <= 10; i++)
		set.insert(i);
	printset(set, false);
	cout << GR << "Insert range" << NC << endl;
	ft::set<int> set2;
	for (int i = 11; i <= 15; i++)
		set2.insert(i);
	cout << HPUR << "set2 contains: " << NC << endl;
	printset(set2, false);
	set.insert(set2.begin(), set2.end());
	printset(set, true);

	// SIZE
	cout << URED << "SIZE" << NC << endl;
	cout << GR << "Size of set" << NC << endl;
	cout << "Size of set is " << set.size() << endl;
	print_sep();

	// FIND
	cout << URED << "FIND" << NC << endl;
	cout << GR << "Looking for 5" << NC << endl;
	ft::set<int>::iterator it = set.find(5);
	if (it != set.end())
		cout << "Found " << *it << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Looking for 155" << NC << endl;
	it = set.find(155);
	if (it != set.end())
		cout << "Found " << *it << endl;
	else
		cout << "Not found" << endl;
	print_sep();
	// COUNT
	cout << URED << "COUNT" << NC << endl;
	cout << GR << "Counting 5" << NC << endl;
	cout << "Count of 5 is " << set.count(5) << endl;
	cout << GR << "Counting 155" << NC << endl;
	cout << "Count of -10 is " << set.count(-10) << endl;
	print_sep();

	// LOWER_BOUND
	cout << URED << "LOWER_BOUND" << NC << endl;
	cout << GR << "Lower bound of 5" << NC << endl;
	it = set.lower_bound(5);
	if (it != set.end())
		cout << "Lower bound of 5 is " << *it << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Lower bound of 155" << NC << endl;
	it = set.lower_bound(155);
	if (it != set.end())
		cout << "Lower bound of 155 is " << *it << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Lower bound of 0" << NC << endl;
	it = set.lower_bound(0);
	if (it != set.end())
		cout << "Lower bound of 0 is " << *it << endl;
	else
		cout << "Not found" << endl;
	print_sep();

	// UPPER_BOUND
	cout << URED << "UPPER_BOUND" << NC << endl;
	cout << GR << "Upper bound of 5" << NC << endl;
	it = set.upper_bound(5);
	if (it != set.end())
		cout << "Upper bound of 5 is " << *it << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Upper bound of 155" << NC << endl;
	it = set.upper_bound(155);
	if (it != set.end())
		cout << "Upper bound of 155 is " << *it << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Upper bound of -10" << NC << endl;
	it = set.upper_bound(-10);
	if (it != set.end())
		cout << "Upper bound of -10 is " << *it << endl;
	else
		cout << "Not found" << endl;
	print_sep();

	// EQUAL_RANGE
	cout << URED << "EQUAL_RANGE" << NC << endl;
	cout << GR << "Equal range of 5" << NC << endl;
	ft::pair<ft::set<int>::iterator, ft::set<int>::iterator> ret;
	ret = set.equal_range(5);
	cout << "Equal range of 5 is " << *ret.first << " " << *ret.second << endl;
	cout << GR << "Equal range of 155" << NC << endl;
	ret = set.equal_range(155);
	if (ret.first != set.end())
		cout << "Equal range of 155 is " << *ret.first << " " << *ret.second << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Equal range of -10" << NC << endl;
	ret = set.equal_range(-10);
	cout << "Equal range of -10 is " << *ret.first << " " << *ret.second << endl;
	print_sep();

	// KEY_COMP
	cout << URED << "KEY_COMP" << NC << endl;
	cout << GR << "Key comparison" << NC << endl;
	ft::set<int>::key_compare comp = set.key_comp();
	it = set.begin();
	ft::set<int>::iterator it2 = set.begin();
	++it2;
	for (; it2 != set.end(); ++it, ++it2)
	{
		cout << YEL << "it : " << *it << " | it2 : " << *it2 << NC << endl;
		if (comp(*it, *it2))
			cout << "it is less than it2" << endl;
		else
			cout << "it is greater than it2" << endl;
	}

	ft::set<int> set3;
	for (int i = 50; i < 65; i++)
		set3.insert(i);
	cout << HPUR << "\nset3 contains : " << NC << endl;
	printset(set3, false);
	cout << HPUR << "set contains : " << NC << endl;
	printset(set, false);
	ft::set<int>::key_compare comp2 = set3.key_comp();
	it = set3.begin();
	it2 = set.begin();
	for (; it2 != set.end(); ++it, ++it2)
	{
		cout << YEL << "it : " << *it << " | it2 : " << *it2 << NC << endl;
		if (comp2(*it, *it2))
			cout << "it is less than it2" << endl;
		else
			cout << "it is greater than it2" << endl;
	}
	print_sep();

	// SWAP
	cout << URED << "SWAP" << NC << endl;
	cout << GR << "Swap set and set3" << NC << endl;
	cout << YEL << "Before swap" << NC << endl;
	cout << HPUR << "set contains : " << NC << endl;
	printset(set, false);
	cout << HPUR << "set3 contains : " << NC << endl;
	printset(set3, false);
	cout << YEL << "After swap" << NC << endl;
	set.swap(set3);
	cout << HPUR << "set contains : " << NC << endl;
	printset(set, false);
	cout << HPUR << "set3 contains : " << NC << endl;
	printset(set3, false);
	print_sep();


	// NON MEMBER OVERLOADS
	cout << URED << "NON MEMBER OVERLOADS" << NC << endl;
	cout << GR << "Non member overloads" << NC << endl;
	cout << YEL << "set == set3" << NC << endl;
	if (set == set3)
		cout << "set is equal to set3" << endl;
	else
		cout << "set is not equal to set3" << endl;
	cout << YEL << "set != set3" << NC << endl;
	if (set != set3)
		cout << "set is not equal to set3" << endl;
	else
		cout << "set is equal to set3" << endl;
	cout << YEL << "set < set3" << NC << endl;
	if (set < set3)
		cout << "set is less than set3" << endl;
	else
		cout << "set is not less than set3" << endl;
	cout << YEL << "set > set3" << NC << endl;
	if (set > set3)
		cout << "set is greater than set3" << endl;
	else
		cout << "set is not greater than set3" << endl;
	cout << YEL << "set <= set3" << NC << endl;
	if (set <= set3)
		cout << "set is less than or equal to set3" << endl;
	else
		cout << "set is not less than or equal to set3" << endl;
	cout << YEL << "set >= set3" << NC << endl;
	if (set >= set3)
		cout << "set is greater than or equal to set3" << endl;
	else
		cout << "set is not greater than or equal to set3" << endl;
	print_sep();

	// CLEAR
	cout << URED << "CLEAR" << NC << endl;
	cout << GR << "Clear set" << NC << endl;
	set.clear();
	cout << YEL << "Size : " << set.size() << NC << endl;
	if (set.empty())
		cout << "set is empty" << endl;
	else
		cout << "set is not empty" << endl;
	printset(set, true);

	// ERASE 
	cout << URED << "ERASE" << NC << endl;
	cout << BLU << "Before erase, set contains : " << NC << endl;
	printset(set3, false);
	it = set3.begin();
	++it;
	cout << YEL << "Erase" << *it << "element of set3" << NC << endl;
	cout << HPUR << "After erase, set contains : " << NC << endl;
	set3.erase(it);
	printset(set3, false);
	cout << YEL << "Erase with key 10" << NC << endl;
	cout << HPUR << "After erase, set contains : " << NC << endl;
	set3.erase(10);
	printset(set3, false);
	it = set3.find(5);
	it2 = set3.find(12);
	cout << YEL << "Erase from " << *it << " to " << *it2 << NC << endl;
	cout << HPUR << "After erase, set contains : " << NC << endl;
	set3.erase(it, it2);
	printset(set3, false);
	cout << YEL << "Try to erase an element [100] that doesn't exist" << NC << endl;
	cout << HPUR << "After erase, set contains : " << NC << endl;
	set3.erase(100);
	printset(set3, false);
	print_sep();

	// CONSTRUCTORS
	cout << URED << "CONSTRUCTORS" << NC << endl;
	cout << YEL << "Create a new set with the copy constructor" << NC << endl;
	ft::set<int> set4(set3);
	cout << HPUR << "set4 contains : " << NC << endl;
	printset(set4, false);
	cout << YEL << "Create a new set with the range constructor from [12] to end of the source set" << NC << endl;
	ft::set<int> set5(set3.find(12), set3.end());
	cout << HPUR << "set5 contains : " << NC << endl;
	printset(set5, false);
	cout << YEL << "Create a new set with the default constructor" << NC << endl;
	ft::set<int> set6;
	cout << HPUR << "set6 contains : " << NC << endl;
	printset(set6, true);

	// OPERATOR=
	cout << URED << "OPERATOR=" << NC << endl;
	cout << YEL << "Assign set3 to set6" << NC << endl;
	set6 = set3;
	printset(set6, true);

	// TEST WITH CHAR
	cout << URED << "TEST WITH CHAR" << NC << endl;
	ft::set<char> set7;
	for (char i = 'a'; i <= 'z'; i++)
		set7.insert(i);
	cout << HPUR << "set with char contains : " << NC << endl;
	for (ft::set<char>::iterator it = set7.begin(); it != set7.end(); it++)
		cout << *it << " | ";
	cout << GR << "\nLooking for element 'c'" << NC << endl;
	ft::set<char>::iterator toFind = set7.find('c');
	cout << YEL << "Element found : " << *toFind << NC << endl;
	cout << GR << "Lower bound of 'c'" << NC << endl;
	ft::set<char>::iterator lower = set7.lower_bound('c');
	cout << YEL << "Lower bound found : " << *lower << NC << endl;
	cout << GR << "Upper bound of 'c'" << NC << endl;
	ft::set<char>::iterator upper = set7.upper_bound('c');
	cout << YEL << "Upper bound found : " << *upper << NC << endl;
	cout << GR << "Equal range of 'c'" << NC << endl;
	ft::pair<ft::set<char>::iterator, ft::set<char>::iterator> range = set7.equal_range('c');
	cout << YEL << "Equal range found : " << *range.first << " and " << *range.second << NC << endl;
	print_sep();

	// SIZE
	cout << URED << "SIZE" << NC << endl;
	cout << "Size of set with char : " << set7.size() << endl;
	cout << "Max size of set with char : " << set7.max_size() << endl;
	print_sep();

	// COPY CONSTRUCTOR
	cout << URED << "COPY CONSTRUCTOR" << NC << endl;
	ft::set<char> set8(set7);
	cout << HPUR << "set8 contains : " << NC << endl;
	for (ft::set<char>::iterator it = set8.begin(); it != set8.end(); it++)
		cout << *it << " | ";
	cout << endl;

	// ERASE
	cout << URED << "ERASE" << NC << endl;
	cout << GR << "Erase from 'a' to 'm' set8" << NC << endl;
	set8.erase(set8.find('a'), set8.find('m'));
	cout << HPUR << "set8 contains : " << NC << endl;
	for (ft::set<char>::iterator it = set8.begin(); it != set8.end(); it++)
		cout << *it << " | ";
	cout << endl;

	// SWAP
	cout << URED << "SWAP" << NC << endl;
	cout << GR << "Swap set7 and set8" << NC << endl;
	set7.swap(set8);
	cout << HPUR << "set7 contains : " << NC << endl;
	for (ft::set<char>::iterator it = set7.begin(); it != set7.end(); it++)
		cout << *it << " | ";
	cout << endl;
	cout << HPUR << "set8 contains : " << NC << endl;
	for (ft::set<char>::iterator it = set8.begin(); it != set8.end(); it++)
		cout << *it << " | ";
	cout << endl;
	return (0);
}