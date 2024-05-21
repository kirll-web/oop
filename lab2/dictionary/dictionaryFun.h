#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <locale.h>
#include <locale>
#include <Windows.h>
#include <optional>
#include <map>
#include <vector>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

bool InitDictionary(std::istream& inputStream, std::map<std::string, std::vector<std::string>>& dictionary);

std::vector<std::string> TranslateWord(std::string const& wordEng, std::map<std::string, std::vector<std::string>> & dictionary);

bool AddNewWordToDictionary(std::string const& wordEng, std::string & wordRus, std::map<std::string, std::vector<std::string>>& dictionary, std::istream& inputStream);

bool SavedChangesInFile(std::string  const& dictionaryFileName, std::map<std::string, std::vector<std::string>> const& dictionary);

bool DictionaryWas—hanged(std::string const & dictionaryFileName, std::map<std::string, std::vector<std::string>> const& dictionary);

bool GetWordEng(std::istream& inputStream, std::string& wordEng);
