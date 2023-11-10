#include "headers/map.hpp"
#include "headers/utils/pair.hpp"
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>

int main(void)
{

    ft::map<int, int> map;
    std::string input;
    std::string separator = " ";

    while (1)
    {
        std::getline(std::cin, input);
        if (std::cin.eof() || input == "exit")
            break;
        if (input.find("insert") != std::string::npos)
        {
            int key = atoi(input.substr(7, input.find(separator)).c_str());
            int value = atoi(input.substr(7 + std::to_string(key).length(), input.length()).c_str());
            map.insert(ft::pair<int, int>(key, value));
        }
        else if (input.find("erase") != std::string::npos)
        {
            int key = atoi(input.substr(5, input.find(separator)).c_str());
            map.erase(key);
        }
        else if (input.find("upper bound") != std::string::npos)
        {
            int key = atoi(input.substr(11, input.find(separator)).c_str());
            ft::map<int, int>::iterator it = map.upper_bound(key);
            if (it != map.end())
                std::cout << "upper bound: " << MAG << it->first << " => " << it->second << NC << std::endl;
            else
                std::cout << "upper bound: " << "end" << std::endl;
        }
        else if (input.find("lower bound") != std::string::npos)
        {
            int key = atoi(input.substr(11, input.find(separator)).c_str());
            ft::map<int, int>::iterator it = map.lower_bound(key);
            if (it != map.end())
                std::cout << "lower bound: " << HPUR << it->first << " => " << it->second << NC << std::endl;
            else
                std::cout << "lower bound: " << "end" << std::endl;
        }
        else if (input.find("find") != std::string::npos)
        {
            int key = atoi(input.substr(4, input.find(separator)).c_str());
            ft::map<int, int>::iterator it = map.find(key);
            if (it != map.end())
                std::cout << "find: " << CYN << it->first << " => " << it->second << NC << std::endl;
            else
                std::cout << "find: " << "end" << std::endl;
        }
        else if (input.find("count") != std::string::npos)
        {
            int key = atoi(input.substr(5, input.find(separator)).c_str());
            std::cout << "count: " << map.count(key) << std::endl;
        }
        else if (input.find("clear") != std::string::npos)
            map.clear();
        else if (input.find("size") != std::string::npos)
            std::cout << "size: " << map.size() << std::endl;
        else if (input.find("empty") != std::string::npos)
            std::cout << "empty: " << map.empty() << std::endl;
        else if (input.find("print") != std::string::npos)
            map.printMap();
        map.printMap();
    }
    return (0);
}