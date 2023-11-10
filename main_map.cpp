#include <iostream>
#include <string>

#define STD 0

#if STD
# define NAMESPACE ft
	#include <map>
	#include "headers/utils/colors.hpp"
	namespace ft = std;
#else
	# define NAMESPACE std
	#include "headers/map.hpp"
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

void	printMap(ft::map<int, int> map, bool printOrNot) 
{
	if (printOrNot)
		std::cout << HPUR << "My map contains: " << NC << std::endl;
	for (ft::map<int, int>::iterator it = map.begin(); it != map.end(); it++)
		cout << it->first << " [ " << it->second << " ] \n";
	if (map.size() == 0)
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
	ft::map<int, int> map;

	// EMPTY
	cout << URED << "EMPTY" << NC << endl;
	cout << GR << "Check if empty" << NC << endl;
	if (map.empty())
		cout << "Map is empty" << endl;
	else
		cout << "Map is not empty" << endl;
	print_sep();

	// INSERT
	cout << URED << "INSERT" << NC << endl;
	cout << GR << "Inserting 1, 2, 3, 4, 5" << NC << endl;
	for (int i = 1; i <= 5; i++)
		map.insert(ft::make_pair(i, i));
	printMap(map, true);

	// EMPTY
	cout << URED << "EMPTY" << NC << endl;
	cout << GR << "Check if empty" << NC << endl;
	if (map.empty())
		cout << "Map is empty" << endl;
	else
		cout << "Map is not empty" << endl;
	print_sep();

	// SIZE
	cout << URED << "SIZE" << NC << endl;
	cout << GR << "Size of map" << NC << endl;
	cout << "Size of map is " << map.size() << endl;
	print_sep();

	// MAX_SIZE
	cout << URED << "MAX_SIZE" << NC << endl;
	cout << GR << "Max size of map" << NC << endl;
	cout << "Max size of map is " << map.max_size() << endl;
	print_sep();

	// INSERT
	cout << URED << "INSERT" << NC << endl;
	cout << GR << "Inserting 6, 7, 8, 9, 10" << NC << endl;
	for (int i = 6; i <= 10; i++)
		map.insert(ft::make_pair(i, i));
	printMap(map, false);
	cout << GR << "Insert range" << NC << endl;
	ft::map<int, int> map2;
	for (int i = 11; i <= 15; i++)
		map2.insert(ft::make_pair(i, i));
	cout << HPUR << "Map2 contains: " << NC << endl;
	printMap(map2, false);
	map.insert(map2.begin(), map2.end());
	printMap(map, true);

	// SIZE
	cout << URED << "SIZE" << NC << endl;
	cout << GR << "Size of map" << NC << endl;
	cout << "Size of map is " << map.size() << endl;
	print_sep();

	// FIND
	cout << URED << "FIND" << NC << endl;
	cout << GR << "Looking for 5" << NC << endl;
	ft::map<int, int>::iterator it = map.find(5);
	if (it != map.end())
		cout << "Found " << it->first << " [ " << it->second << " ] " << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Looking for 155" << NC << endl;
	it = map.find(155);
	if (it != map.end())
		cout << "Found " << it->first << " [ " << it->second << " ] " << endl;
	else
		cout << "Not found" << endl;
	print_sep();
	// COUNT
	cout << URED << "COUNT" << NC << endl;
	cout << GR << "Counting 5" << NC << endl;
	cout << "Count of 5 is " << map.count(5) << endl;
	cout << GR << "Counting 155" << NC << endl;
	cout << "Count of -10 is " << map.count(-10) << endl;
	print_sep();

	// LOWER_BOUND
	cout << URED << "LOWER_BOUND" << NC << endl;
	cout << GR << "Lower bound of 5" << NC << endl;
	it = map.lower_bound(5);
	if (it != map.end())
		cout << "Lower bound of 5 is " << it->first << " [ " << it->second << " ] " << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Lower bound of 155" << NC << endl;
	it = map.lower_bound(155);
	if (it != map.end())
		cout << "Lower bound of 155 is " << it->first << " [ " << it->second << " ] " << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Lower bound of 0" << NC << endl;
	it = map.lower_bound(0);
	if (it != map.end())
		cout << "Lower bound of 0 is " << it->first << " [ " << it->second << " ] " << endl;
	else
		cout << "Not found" << endl;
	print_sep();

	// UPPER_BOUND
	cout << URED << "UPPER_BOUND" << NC << endl;
	cout << GR << "Upper bound of 5" << NC << endl;
	it = map.upper_bound(5);
	if (it != map.end())
		cout << "Upper bound of 5 is " << it->first << " [ " << it->second << " ] " << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Upper bound of 155" << NC << endl;
	it = map.upper_bound(155);
	if (it != map.end())
		cout << "Upper bound of 155 is " << it->first << " [ " << it->second << " ] " << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Upper bound of -10" << NC << endl;
	it = map.upper_bound(-10);
	if (it != map.end())
		cout << "Upper bound of -10 is " << it->first << " [ " << it->second << " ] " << endl;
	else
		cout << "Not found" << endl;
	print_sep();

	// EQUAL_RANGE
	cout << URED << "EQUAL_RANGE" << NC << endl;
	cout << GR << "Equal range of 5" << NC << endl;
	ft::pair<ft::map<int, int>::iterator, ft::map<int, int>::iterator> ret;
	ret = map.equal_range(5);
	cout << "Equal range of 5 is " << ret.first->first << " [ " << ret.first->second << " ] " << " and " << ret.second->first << " [ " << ret.second->second << " ] " << endl;
	cout << GR << "Equal range of 155" << NC << endl;
	ret = map.equal_range(155);
	if (ret.first != map.end())
		cout << "Equal range of 155 is " << ret.first->first << " [ " << ret.first->second << " ] " << " and " << ret.second->first << " [ " << ret.second->second << " ] " << endl;
	else
		cout << "Not found" << endl;
	cout << GR << "Equal range of -10" << NC << endl;
	ret = map.equal_range(-10);
	cout << "Equal range of -10 is " << ret.first->first << " [ " << ret.first->second << " ] " << " and " << ret.second->first << " [ " << ret.second->second << " ] " << endl;
	print_sep();

	// KEY_COMP
	cout << URED << "KEY_COMP" << NC << endl;
	cout << GR << "Key comparison" << NC << endl;
	ft::map<int, int>::key_compare comp = map.key_comp();
	it = map.begin();
	ft::map<int, int>::iterator it2 = map.begin();
	++it2;
	for (; it2 != map.end(); ++it, ++it2)
	{
		cout << YEL << "it : " << (*it).first << " | it2 : " << (*it2).first << NC << endl;
		if (comp((*it).first, (*it2).first))
			cout << "it is less than it2" << endl;
		else
			cout << "it is greater than it2" << endl;
	}

	ft::map<int, int> map3;
	for (int i = 50; i < 65; i++)
		map3.insert(ft::make_pair(i, i * 10));
	cout << HPUR << "\nMap3 contains : " << NC << endl;
	printMap(map3, false);
	cout << HPUR << "Map contains : " << NC << endl;
	printMap(map, false);
	ft::map<int, int>::key_compare comp2 = map3.key_comp();
	it = map3.begin();
	it2 = map.begin();
	for (; it2 != map.end(); ++it, ++it2)
	{
		cout << YEL << "it : " << (*it).first << " | it2 : " << (*it2).first << NC << endl;
		if (comp2((*it).first, (*it2).first))
			cout << "it is less than it2" << endl;
		else
			cout << "it is greater than it2" << endl;
	}
	print_sep();

	// OPERATOR[]
	cout << URED << "OPERATOR[]" << NC << endl;
	cout << GR << "Operator []" << NC << endl;
	cout << "assigning 100 to map[5]" << endl;
	map[5] = 100;
	cout << "assigning 1000 to map[155]" << endl;
	map[155] = 1000;
	cout << "assigning 0 to map[0]" << endl;
	map[0] = 24;
	printMap(map, true);

	// SWAP
	cout << URED << "SWAP" << NC << endl;
	cout << GR << "Swap map and map3" << NC << endl;
	cout << YEL << "Before swap" << NC << endl;
	cout << HPUR << "Map contains : " << NC << endl;
	printMap(map, false);
	cout << HPUR << "Map3 contains : " << NC << endl;
	printMap(map3, false);
	cout << YEL << "After swap" << NC << endl;
	map.swap(map3);
	cout << HPUR << "Map contains : " << NC << endl;
	printMap(map, false);
	cout << HPUR << "Map3 contains : " << NC << endl;
	printMap(map3, false);
	print_sep();


	// NON MEMBER OVERLOADS
	cout << URED << "NON MEMBER OVERLOADS" << NC << endl;
	cout << GR << "Non member overloads" << NC << endl;
	cout << YEL << "Map == Map3" << NC << endl;
	if (map == map3)
		cout << "Map is equal to Map3" << endl;
	else
		cout << "Map is not equal to Map3" << endl;
	cout << YEL << "Map != Map3" << NC << endl;
	if (map != map3)
		cout << "Map is not equal to Map3" << endl;
	else
		cout << "Map is equal to Map3" << endl;
	cout << YEL << "Map < Map3" << NC << endl;
	if (map < map3)
		cout << "Map is less than Map3" << endl;
	else
		cout << "Map is not less than Map3" << endl;
	cout << YEL << "Map > Map3" << NC << endl;
	if (map > map3)
		cout << "Map is greater than Map3" << endl;
	else
		cout << "Map is not greater than Map3" << endl;
	cout << YEL << "Map <= Map3" << NC << endl;
	if (map <= map3)
		cout << "Map is less than or equal to Map3" << endl;
	else
		cout << "Map is not less than or equal to Map3" << endl;
	cout << YEL << "Map >= Map3" << NC << endl;
	if (map >= map3)
		cout << "Map is greater than or equal to Map3" << endl;
	else
		cout << "Map is not greater than or equal to Map3" << endl;
	print_sep();

	// CLEAR
	cout << URED << "CLEAR" << NC << endl;
	cout << GR << "Clear map" << NC << endl;
	map.clear();
	cout << YEL << "Size : " << map.size() << NC << endl;
	if (map.empty())
		cout << "Map is empty" << endl;
	else
		cout << "Map is not empty" << endl;
	printMap(map, true);

	// ERASE 
	cout << URED << "ERASE" << NC << endl;
	cout << BLU << "Before erase, map contains : " << NC << endl;
	printMap(map3, false);
	it = map3.begin();
	++it;
	cout << YEL << "Erase" << it->first << " [ " << it->second << " ] " << "element of map3" << NC << endl;
	cout << HPUR << "After erase, map contains : " << NC << endl;
	map3.erase(it);
	printMap(map3, false);
	cout << YEL << "Erase with key 10" << NC << endl;
	cout << HPUR << "After erase, map contains : " << NC << endl;
	map3.erase(10);
	printMap(map3, false);
	it = map3.find(5);
	it2 = map3.find(12);
	cout << YEL << "Erase from " << it->first << " [ " << it->second << " ] to " << it2->first << " [ " << it2->second << " ] " << NC << endl;
	cout << HPUR << "After erase, map contains : " << NC << endl;
	map3.erase(it, it2);
	printMap(map3, false);
	cout << YEL << "Try to erase an element [100] that doesn't exist" << NC << endl;
	cout << HPUR << "After erase, map contains : " << NC << endl;
	map3.erase(100);
	printMap(map3, false);
	print_sep();

	// CONSTRUCTORS
	cout << URED << "CONSTRUCTORS" << NC << endl;
	cout << YEL << "Create a new map with the copy constructor" << NC << endl;
	ft::map<int, int> map4(map3);
	cout << HPUR << "Map4 contains : " << NC << endl;
	printMap(map4, false);
	cout << YEL << "Create a new map with the range constructor from [12] to end of the source map" << NC << endl;
	ft::map<int, int> map5(map3.find(12), map3.end());
	cout << HPUR << "Map5 contains : " << NC << endl;
	printMap(map5, false);
	cout << YEL << "Create a new map with the default constructor" << NC << endl;
	ft::map<int, int> map6;
	cout << HPUR << "Map6 contains : " << NC << endl;
	printMap(map6, true);

	// OPERATOR=
	cout << URED << "OPERATOR=" << NC << endl;
	cout << YEL << "Assign map3 to map6" << NC << endl;
	map6 = map3;
	printMap(map6, true);

	// TEST WITH CHAR
	cout << URED << "TEST WITH CHAR" << NC << endl;
	ft::map<char, int> map7;
	for (char i = 'a'; i <= 'z'; i++)
		map7.insert(ft::make_pair(i, i - 96));
	cout << HPUR << "map with char contains : " << NC << endl;
	for (ft::map<char, int>::iterator it = map7.begin(); it != map7.end(); it++)
		cout << it->first << " [ " << it->second << " ] " << endl;
	cout << endl;
	cout << GR << "\nLooking for element 'c'" << NC << endl;
	ft::map<char, int>::iterator toFind = map7.find('c');
	cout << YEL << "Element found : " << toFind->first << " [ " << toFind->second << " ]"<<  NC << endl;
	cout << GR << "Lower bound of 'c'" << NC << endl;
	ft::map<char, int>::iterator lower = map7.lower_bound('c');
	cout << YEL << "Lower bound found : " << lower->first << " [ " << lower->second << " ]" << NC << endl;
	cout << GR << "Upper bound of 'c'" << NC << endl;
	ft::map<char, int>::iterator upper = map7.upper_bound('c');
	cout << YEL << "Upper bound found : " << upper->first << " [ " << upper->second << " ]" << NC << endl;
	cout << GR << "Equal range of 'c'" << NC << endl;
	ft::pair<ft::map<char, int>::iterator, ft::map<char, int>::iterator> range = map7.equal_range('c');
	cout << YEL << "Equal range found : " << range.first->first << " [ " << range.first->second << " ]" << " | " << range.second->first << " [ " << range.second->second << " ]" << NC << endl;
	print_sep();

	// SIZE
	cout << URED << "SIZE" << NC << endl;
	cout << "Size of map with char : " << map7.size() << endl;
	cout << "Max size of map with char : " << map7.max_size() << endl;
	print_sep();

	// COPY CONSTRUCTOR
	cout << URED << "COPY CONSTRUCTOR" << NC << endl;
	ft::map<char, int> map8(map7);
	cout << HPUR << "map8 contains : " << NC << endl;
	for (ft::map<char, int>::iterator it = map8.begin(); it != map8.end(); it++)
		cout << it->first << " [ " << it->second << " ] " << endl;
	cout << endl;

	// ERASE
	cout << URED << "ERASE" << NC << endl;
	cout << GR << "Erase from 'a' to 'm' map8" << NC << endl;
	map8.erase(map8.find('a'), map8.find('m'));
	cout << HPUR << "map8 contains : " << NC << endl;
	for (ft::map<char, int>::iterator it = map8.begin(); it != map8.end(); it++)
		cout << it->first << " [ " << it->second << " ] " << endl;
	cout << endl;

	// SWAP
	cout << URED << "SWAP" << NC << endl;
	cout << GR << "Swap map7 and map8" << NC << endl;
	map7.swap(map8);
	cout << HPUR << "map7 contains : " << NC << endl;
	for (ft::map<char, int>::iterator it = map7.begin(); it != map7.end(); it++)
		cout << it->first << " [ " << it->second << " ] " << endl;
	cout << endl;
	cout << HPUR << "map8 contains : " << NC << endl;
	for (ft::map<char, int>::iterator it = map8.begin(); it != map8.end(); it++)
		cout << it->first << " [ " << it->second << " ] " << endl;
	cout << endl;
	map8.printMap();
	return (0);
}