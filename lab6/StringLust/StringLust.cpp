#include <iostream>
#include "CStringList.h"
#include <vector>


int main()
{
    CStringList list;
    list.Push_back("1");
    list.Push_back("1");
    std::vector<int> vec{ 1,2,3 };
    for (auto it = vec.end() - 1; it != vec.begin();it--)
    {
        std::cout << *it;
        std::cout << *vec.begin();
    }
    for (auto it = list.end() - 1; it != list.begin(); --it)
    {
        std::cout << *it;
    }

    for (auto it = list.begin(); it != list.end(); it++)
    {
        std::cout << *it;
    }

    

    
}
