// tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../dictionary/dictionaryFun.h"
#include <vector>
#include <locale.h>
#include <locale>



SCENARIO("initDictionary")
{

	std::map<std::string, std::vector<std::string>> expectedDictionary, resultDictionary;
	expectedDictionary["bag"].push_back("сумка");
	expectedDictionary["cat"].push_back("кошка");
	expectedDictionary["dog"].push_back("собака");
	expectedDictionary["tea"].push_back("чай");
	expectedDictionary["tea"].push_back("напиток");

	std::ifstream dictionFile("dict2.txt");

	InitDictionary(dictionFile, resultDictionary);

	REQUIRE(expectedDictionary == resultDictionary);
}

SCENARIO("addNewWordDictionary return true")
{
	std::locale rus("russian");
	std::locale::global(rus);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::map<std::string, std::vector<std::string>> resultDictionary;
	std::string wordEng = "bag";

	
	resultDictionary["cat"].push_back("кошка");
	resultDictionary["dog"].push_back("собака");
	resultDictionary["tea"].push_back("чай");
	resultDictionary["tea"].push_back("напиток");
	
	std::istringstream wordRus("сумка");
	std::string str;
	REQUIRE(AddNewWordToDictionary(wordEng, str, resultDictionary, wordRus));
}



SCENARIO("addNewWordDictionary return false. Enter only Ctrl+Z")
{
	std::locale rus("russian");
	std::locale::global(rus);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::map<std::string, std::vector<std::string>> resultDictionary;
	std::string wordEng = "bag";
	std::string str;

	std::stringstream stream('\x1a');
	REQUIRE(AddNewWordToDictionary(wordEng, str, resultDictionary, stream));
}

SCENARIO("addNewWordDictionary return false. Enter word this Ctrl+Z")
{
	std::locale rus("russian");
	std::locale::global(rus);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::map<std::string, std::vector<std::string>> resultDictionary;
	std::string wordEng = "bag";
	std::string str;

	std::stringstream stream('\x1a');
	REQUIRE(AddNewWordToDictionary(wordEng, str, resultDictionary, stream));
}

SCENARIO("addNewWordDictionary. WordEng is empty")
{
	std::locale rus("russian");
	std::locale::global(rus);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::map<std::string, std::vector<std::string>> resultDictionary;
	std::string wordEng = "";
	std::string str;
	std::stringstream stream("");
	REQUIRE(!AddNewWordToDictionary(wordEng, str, resultDictionary, stream));
}

SCENARIO("GetWordEng. WordEng is empty")
{
	std::locale rus("russian");
	std::locale::global(rus);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	std::string wordEng;
	std::stringstream stream("");

	REQUIRE(!GetWordEng(stream, wordEng));
}

SCENARIO("GetWordEng. WordEng is ...")
{
	std::locale rus("russian");
	std::locale::global(rus);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string wordEng;
	std::stringstream stream("...");

	REQUIRE(!GetWordEng(stream, wordEng));
}

SCENARIO("GetWordEng. WordEng is ctrl+z")
{
	std::string wordEng;

	std::stringstream stream('\x1a');

	REQUIRE(!GetWordEng(stream, wordEng));
}

SCENARIO("GetWordEng. WordEng is normal")
{
	std::locale rus("russian");
	std::locale::global(rus);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::string wordEng;
	std::stringstream stream("length");

	REQUIRE(GetWordEng(stream, wordEng) == true);
}





