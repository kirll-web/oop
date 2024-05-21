
#include <iostream>
#include "CDate.h"



int main()
{
	CDate date{ 11, Month::MAY, 2024 };
	std::cout << static_cast<unsigned>(date.GetWeekDay());
	return 0;
}
