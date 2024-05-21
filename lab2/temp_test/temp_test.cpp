// temp_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"

#include "../expand_template/temp.h"

SCENARIO("emptry str gives empty string")
{
	REQUIRE(Temp("").empty());
}

SCENARIO("length 1")
{
	REQUIRE(Temp("a") == "a");
}