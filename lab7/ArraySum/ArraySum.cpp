
#include <iostream>
#include "FArraySum.h"
int main()
{
    std::vector<std::string> emptyArr;
    std::cout << "emptyArr: "  << ArraySum(emptyArr) << std::endl;

    std::vector<std::string> stringsArr{"abc", "dfgh"};
    std::cout << "stringsArr: " << ArraySum(stringsArr) << std::endl;

    std::vector<int> intArr{ 1, 2, 3 };
    std::cout << "intArr: " << ArraySum(intArr) << std::endl;

    std::vector<double> doubleArr{ 1.2, 2.2, 3.3 };
    std::cout << "doubleArr: " << ArraySum(doubleArr) << std::endl;
}
