#include "MulOnMinimalElement.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

const int NUMBER_PRECISION = 3;

void ReadInput(std::vector<double>& numbers)
{
	std::cout << "Input values of range. Click enter or other char key for stop it: " << std::endl;
	std::string line;
	std::getline(std::cin, line);
	std::istringstream in(line, std::istringstream::in);

	double num;

	while (in >> num) 
	{
		numbers.push_back(num);
	}
}


void OutputResult(const std::vector<double>& numbers)
{
	std::cout << "result: ";
	for (double i : numbers)
	{
		std::cout << std::setprecision(NUMBER_PRECISION) << std::fixed << i << " ";
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<double> numbers;

	ReadInput(numbers);

	if (numbers.size() > 0)
	{
		MulOnMinimalElement(numbers);
		std::sort(numbers.begin(), numbers.end());

		OutputResult(numbers);
	}
	else
	{
		std::cout << "range is empty" << std::endl;
	}

	return 0;
	
}