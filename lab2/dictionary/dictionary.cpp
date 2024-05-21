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
#include "dictionaryFun.h"


const std::string END_OF_STRING = "...";
struct Args
{
    std::string dictionaryFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: miniDictionary.exe <input file>\n";
        return std::nullopt;
    }

    Args args;
    args.dictionaryFileName = argv[1];
    return args;
}

void InitLocale()
{
    std::locale rus("russian");
    std::locale::global(rus);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

void OutputTranslatedWord(std::string wordEng, std::vector<std::string> traslatedWords)
{
    std::cout << "Cлово " << wordEng << " переводится как  " << std::endl;
    for (std::string word : traslatedWords)
    {
        std::cout << word << std::endl;
    }
}

bool StartTranslateFromFile(std::string dictionaryFileName)
{
    std::ifstream dictionaryFile(dictionaryFileName);
    std::map<std::string, std::vector<std::string>> dictionary;
    std::string wordEng;

    //разделить if
    if (dictionaryFile.is_open())
    {
        if (!InitDictionary(dictionaryFile, dictionary)) 
        {
                return false;
        }
    }
   
    size_t dictionarySize = dictionary.size();

    while (!std::cin.eof() && GetWordEng(std::cin, wordEng))
    {
        std::vector<std::string> traslatedWords = TranslateWord(wordEng, dictionary);
        std::string wordRus;
        if (traslatedWords.empty() && !AddNewWordToDictionary(wordEng, wordRus, dictionary, std::cin))
        {
            if (wordRus == END_OF_STRING)
            {
                break;
            }
            return false;
        }

        if (!traslatedWords.empty())
        {
            OutputTranslatedWord(wordEng, traslatedWords);
        }
    }

    dictionaryFile.close();

    if (dictionarySize != dictionary.size() && !std::cin.eof())
    {
        return DictionaryWasСhanged(dictionaryFileName, dictionary);
    }

    return true;
}


int main(int argc, char* argv[])
{
    InitLocale();
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }

    if(!StartTranslateFromFile(args->dictionaryFileName))
    {
        return 1;
    }

    std::cout << "Досвидания!" << std::endl;
    return 0;
}