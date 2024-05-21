// tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "../RemoveExtraSpaces/RemoveExtraSpacesFromStr.h"
#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include <vector>

SCENARIO("from ' 2   2  ' to '2 2'")
{
	std::string startString = " 2   2  ";
	std::string finishString = RemoveExtraSpacesFromStr(startString);
	std::string exceptStr = "2 2";

	REQUIRE(exceptStr == finishString);
}

SCENARIO("from '2sd   2  ' to '2sd 2'")
{
	std::string startString = "2sd   2  ";
	std::string finishString = RemoveExtraSpacesFromStr(startString);
	std::string exceptStr = "2sd 2";

	REQUIRE(exceptStr == finishString);
}

SCENARIO("from '  2abcd' to '2'")
{
	std::string startString = "  2abcd";
	std::string finishString = RemoveExtraSpacesFromStr(startString);
	std::string exceptStr = "2abcd";

	REQUIRE(exceptStr == finishString);
}


SCENARIO("from ' ' to ''")
{
	std::string startString = " ";
	std::string finishString = RemoveExtraSpacesFromStr(startString);
	std::string exceptStr = "";

	REQUIRE(exceptStr == finishString);
}

