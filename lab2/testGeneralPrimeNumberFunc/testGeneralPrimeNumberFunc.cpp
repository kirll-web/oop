// tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "../GeneratePrimeNumbers/GeneratePrimeNumbersFunc.h"
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>
#include <set>

SCENARIO("In 11 prime numbers  2, 3, 5, 7, 11 ")
{	
	int checkNum = 11;
	std::set<int> expectedResult{ 2, 3, 5, 7, 11 };
	std::set<int> result = GeneratePrimeNumbersSet(checkNum);

	REQUIRE(equal(result.begin(), result.end(), expectedResult.begin()));
}

SCENARIO("In 5 prime numbers  2, 3, 5")
{
	int checkNum = 5;
	std::set<int> expectedResult{ 2, 3, 5};
	std::set<int> result = GeneratePrimeNumbersSet(checkNum);

	REQUIRE(equal(result.begin(), result.end(), expectedResult.begin()));
}


SCENARIO("In 6 prime numbers  2, 3, 5, ")
{
	int checkNum = 6;
	std::set<int> expectedResult{ 2, 3, 5 };
	std::set<int> result = GeneratePrimeNumbersSet(checkNum);

	REQUIRE(equal(result.begin(), result.end(), expectedResult.begin()));
}

SCENARIO("In 21 prime numbers  2, 3, 5, 7, 11, 13, 17, 19")
{
	int checkNum = 21;
	std::set<int> expectedResult{ 2, 3, 5, 7, 11, 13, 17, 19};
	std::set<int> result = GeneratePrimeNumbersSet(checkNum);

	REQUIRE(equal(result.begin(), result.end(), expectedResult.begin()));
}
//сделать проверку на пограниченные значения
SCENARIO("In 100000000 prime numbers has size 5761455")
{
	int checkNum = 100000000;
	int expectedSizeResult = 5761455;
	std::set<int> result = GeneratePrimeNumbersSet(checkNum);

	REQUIRE(result.size() == expectedSizeResult);
}

