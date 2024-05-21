
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <locale>
#include <optional>
#include <string>
#include <functional>

const std::string ACTION_CRYPT = "crypt";
const std::string ACTION_DECRYPT = "decrypt";

struct Args 
{
    std::string action;
    std::string inputFileName;
    std::string outputFileName;
    std::string key;
};

std::optional<Args> ParseArgs(int argc, char* argv[]) 
{
    if (argc != 5)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: crypt.exe <crypt/decrypt> <input file> <output file> <key>\n";
        return std::nullopt;
    }

    Args args;
    args.action = argv[1];
    args.inputFileName = argv[2];
    args.outputFileName = argv[3];
    args.key = argv[4];
    return args;
}

using ModifiedCharFn = std::function<char(char x, int key)>;

char Crypt(char const ch, int key)
{
    char x = ch;
    x ^= key;
    return ((x << 2) & 28) |
        ((x >> 5) & 3) |
        ((x << 3) & 192) |
        ((x >> 2) & 32);
}

//функции должны быть названы как положено
char Decrypt(char const ch, int key)
{
    char x = ch;
     //в двоичной. а не 16
    x = ((x & 28) >> 2) |
        ((x & 3) << 5) |
        ((x & 192) >> 3) |
        ((x & 32) << 2);
    x ^= key;
    return x;
}

bool CheckFailedReadFile(std::istream& file)
{
    if (file.bad())
    {
        std::cout << "Failed to read data from input file." << std::endl;
        return false;
    }
    
    return true;
}

bool CheckFailedSaveToFile(std::ostream& file, char ch)
{
    if (!file.put(ch))
    {
        std::cout << "Failed to save data on disk" << std::endl;
        return false;
    }
    return true;
}

bool ApplyActionToStream(std::istream& inputFile, std::ostream& outputFile, int key, const ModifiedCharFn& callback = ModifiedCharFn())
{
    char ch;

    while (inputFile.get(ch))
    {
        ch = callback(ch, key);
        if (!CheckFailedSaveToFile(outputFile, ch))
        {
            return false;
        }
    }

    if (!CheckFailedReadFile(inputFile))
    {
        return false;
    }
    //проверить на успешность после окончания чтения

    return true;
}

void InitLocale()
{
    std::locale rus("russian");
    std::locale::global(rus);
}

bool ApplyAction(std::istream& inputFile, std::ostream& outputFile, int key, std::string action)
{
    if (action == ACTION_CRYPT)
    {
        ApplyActionToStream(inputFile, outputFile, key, Crypt);

    }
    else if (action == ACTION_DECRYPT)
    {
        ApplyActionToStream(inputFile, outputFile, key, Decrypt);
    }
    else
    {
        std::cout << "choosed incorrect action" << std::endl;
        return false;
    }

    return true;
}


bool OpenFiles(std::ifstream& inputFile, std::ofstream& outputFile, std::string & inputFileName, std::string& outputFileName)
{
    inputFile.open(inputFileName, std::ios::binary);

    if (!inputFile.is_open())
    {
        std::cout << "Failed to open " << inputFileName << " for reading";

        return false;
    }

    outputFile.open(outputFileName, std::ios::binary);

    if (!outputFile.is_open()) 
    {
        std::cout << "Failed to open " << outputFileName << " for reading";
        return false;
    }

    return true;
}


bool InitKey(int & key, std::string keyString)
{
    try
    {
        key = std::stoi(keyString);
    }
    catch (std::exception&)
    {
        std::cout << "key is not a number" << std::endl;
        return false;
    }

    if (key < 0 || key > 255)
    {
        std::cout << "Invalid key entered" << std::endl;
        return false;
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

    int key;

    if (!InitKey(key, args->key))
    {
        return 1;
    }

    std::ifstream inputFile;
    std::ofstream outputFile;

    if (!OpenFiles(inputFile, outputFile, args->inputFileName, args->outputFileName))
    {
        return 1;
    }

    std::string action = args->action;
    if (!ApplyAction(inputFile, outputFile, key, action))
    {
        return 1;
    }

    if (!CheckFailedReadFile(inputFile))
    {
        return 1;
    }

    return 0;
}
