// tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "../VectorTask/MulOnMinimalElement.h"
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>

SCENARIO("min elem 2 mul on elements 5 4 2 9")
{
	std::vector<double> vec{ 5,4,2,9 };
	std::vector<double> testVec{ 10,8,4,18 };
	MulOnMinimalElement(vec);

	REQUIRE(vec == testVec);
}

SCENARIO("min elem 0.1 mul on elements 5 4 0.1 0.2 100")
{
	std::vector<double> vec{ 5, 4, 0.1, 0.2, 100 };
	std::vector<double> testVec{ 5 * 0.1, 4 * 0.1, 0.1 * 0.1,0.2 * 0.1, 100 * 0.1, };
	MulOnMinimalElement(vec);

	REQUIRE(vec == testVec);
}

SCENARIO("min elem -100 mul on elements 5 4 0.1 0.2 100")
{
	std::vector<double> vec{ 5, 4, 0.1, 0.2, -100 };
	std::vector<double> testVec{ 5 * 0.1, 4 * 0.1, 0.1 * 0.1,0.2 * 0.1, 100 * 0.1, };
	MulOnMinimalElement(vec);

	REQUIRE(vec == testVec);
}

SCENARIO("empty vector")
{
	std::vector<double> vec{ };
	std::vector<double> expectedVec{ };
	MulOnMinimalElement(vec);

	REQUIRE(vec == expectedVec);
}