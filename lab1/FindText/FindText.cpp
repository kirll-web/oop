
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <locale.h>
#include <locale>
#include <optional>
#include <string>

struct Args 
{
    std::string inputFileName;
    std::string findString;
};

std::optional<Args> ParseArgs(int argc, char* argv[]) 
{
    if (argc != 3)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: findtext.cpp <input file name> <output file name> <findtext>\n";
        return std::nullopt;
    }

    Args args;
    args.inputFileName = argv[1];
    args.findString = argv[2];
    return args;
}

//ifstream заменить на istream
bool FindText(std::istream& inputFile, std::string& findString)
{
    char ch;
    int i = 0;
    int lineCounter = 1;
    bool isFound = false;
    while (inputFile.get(ch))
    {
        if (ch == findString[i])
        {
            if (i == findString.length() - 1)
            {
                // endl
                std::cout << "Text found in string: " << lineCounter << std::endl;
                isFound = true;
                i = 0;
            }
            i++;
        }
        else
        {
            if (ch == '\n') {
                lineCounter++;
            }
            i = 0;
        }
    }

    return isFound;
}

bool OpenInputFile(std::ifstream &inputFile, std::string const& inputFileName) 
{
    inputFile.open(inputFileName);
    if (!inputFile.is_open())
    {
        std::cout << "Failed to open " << inputFileName  << " for reading \n";
        return false;
    }
    return true;
}

void InitLocale()
{
    std::locale rus("russian");// вынести в отдельную процедуру
    std::locale::global(rus);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

int main(int argc, char* argv[])
{
    InitLocale();
    auto args = ParseArgs(argc, argv);

    if (!args) 
    {
        return 1;
    }

    std::string findString = args->findString;

    std::ifstream inputFile;
    
    if (OpenInputFile(inputFile, args->inputFileName))
    {
        return 1;
    }

    if (!FindText(inputFile, findString)) 
    {
        std::cout << "Text not found\n";
        return 1;
    }

    if (inputFile.bad())
    {
        std::cout << "Failed to read data from input file " << argv[1] << "\n";
        return 1;
    }

    return 0;
}



