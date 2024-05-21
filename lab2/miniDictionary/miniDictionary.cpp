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

struct Args
{
    std::string inputFileName;
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
    args.inputFileName = argv[1];
    return args;
}

void InitLocale()
{
    std::locale rus("russian");
    std::locale::global(rus);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

bool AddWordToDictionary(std::string const& wordEng, std::string const& wordRus, std::map<std::string, std::vector<std::string>>& dictionary)
{
    if (wordRus != "" && wordEng != "")
    {
        dictionary[wordEng].push_back(wordRus);
        return true;
    }

    return false;
}



std::string ReadWordFromInput()
{
    std::string word;
    char ch = ' ';
    while (ch != '\x1a' && ch != '\n' && std::cin.get(ch)) 
    {
        if (ch != '\x1a' && ch != '\n')
        {
            word += ch;
        }
    }

    return word;
}

void AddNewWordToDictionary(std::string const& input ,std::map<std::string, std::vector<std::string>>& dictionary)
{
    std::string wordRus;
    std::cout << "Unknow word. Enter traslation word for it or emptry string: ";
    wordRus = ReadWordFromInput();
    
    if (AddWordToDictionary(input, wordRus, dictionary))
    {
        std::cout << input << " — " << wordRus << " is saved." << std::endl;
    }
}
//использовать const
void OutputTranslatedWords(std::map<std::string, std::vector<std::string>> & dictionary, std::string const& input)
{
    std::cout << "Translation of a word:";
    for (const auto &word : dictionary[input])
    {
        std::cout << " " << word;
    }
    std::cout << std::endl;
}

void StartTranslate(std::map<std::string, std::vector<std::string>>& dictionary)
{
    std::string input = "";
    
    while (input != "..." && !std::cin.eof())
    {
        std::cout << "Enter the word to translate. Enter the word to translate. To close the program, enter \"...\"" << std::endl;
        input = ReadWordFromInput();
        
        if (input != "..." && input.length() > 0)
        {
            //избавиться от дублирующего сравнения на выход из программы ...
            if (dictionary.count(input) > 0)
            {
                OutputTranslatedWords(dictionary, input);
            }
            else
            {
                AddNewWordToDictionary(input, dictionary);
            }
        }
    }
}

void SaveWordsToFile(std::map<std::string, std::vector<std::string>>& dictionary, std::ostream & outputFile) 
{
    for (auto it = dictionary.begin(); it != dictionary.end(); ++it)
    {
        outputFile << it->first << std::endl;

        for (auto word : it->second)
        {
            outputFile << word << ",";
        }
        outputFile << std::endl;
    }
}

void SaveChanges(std::map<std::string, std::vector<std::string>>& dictionary, std::string outputFileName)
{

    char choice;
    std::cout << "Changes have been made to the dictionary.Enter Y or y to save before exiting:" << std::endl;
    if (std::cin.eof())
    {
        std::cin.clear();
    }
    std::cin.get(choice);

    if (choice == 'Y' || choice == 'y')
    {
        std::ofstream outputFile(outputFileName);

        SaveWordsToFile(dictionary, outputFile);
    }
    //узнать как работает getline при конце файла и объяснить проверяющему
}

int main(int argc, char* argv[])
{
    InitLocale();
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }

    std::ifstream inputFile(args->inputFileName);

    std::map<std::string, std::vector<std::string>> dictionary;
    if (inputFile.is_open())
    {
        InitDictionary(inputFile, dictionary);
    }

    size_t lengthDictionary = dictionary.size();
    StartTranslate(dictionary);

    if (lengthDictionary != dictionary.size())
    {
        inputFile.close();
        SaveChanges(dictionary, args->inputFileName);
    }

    std::cout << "Goodbye!" << std::endl;

    return 0;
}