#include <iostream>
#include "CStringList.h"
#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <fstream>


int main()
{
    CStringList list;
    CStringList list2;
    list.push_front("1");
    list.push_front("2");
    list.push_front("3");
    list.push_front("4");

    std::list<int> listStl;
    listStl.push_back(1);
    listStl.push_back(2);
    listStl.push_back(3);

    auto it = std::transform(list.begin(), list.end(), std::back_inserter(list2), [](std::string n) 
        { return n + "abcd"; });
    //std::for_each(list2.begin(), list2.end(), [](std::string it) {
    //    std::cout << it; 
    //});

    list2.Clear();

    std::copy(list.begin(), list.end(), std::back_inserter(list2));

    std::for_each(list2.begin(), list2.end(), [](std::string it) {
        std::cout << it;
     });
}
