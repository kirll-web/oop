
#include <iostream>
#include "CDate.h"
int main()
{
	CDate date{ 1, Month::FEBRUARY, 2009 };

	std::cout << date.GetDay();
}
