#include <iostream>
#include "CStringList.h"
#include <vector>
#include <algorithm>


int main()
{
    CStringList list;
    list.Push_back("1");
    list.Push_back("2");
    list.Push_back("3");
    list.Push_back("4");
    CStringList list2;
    std::sort(list.begin(), list.end(), list2);
}
