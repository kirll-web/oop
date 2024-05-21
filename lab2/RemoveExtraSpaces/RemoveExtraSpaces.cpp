#include <iostream>
#include <fstream>
#include <optional>
#include "RemoveExtraSpacesFromStr.h"

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: <input file> <output file>\n";
        return std::nullopt;
    }

    Args args;
    args.inputFileName = argv[1];
    args.outputFileName = argv[2];
    return args;
}



bool OpenFiles(std::ifstream& inputFile, std::ofstream& outputFile, std::string inputFileName, std::string outputFileName)
{
    inputFile.open(inputFileName);
    if (!inputFile.is_open())
    {
        std::cout << "Input file is not open." << std::endl;
        return false;
    }

    outputFile.open(outputFileName);

    return true;
}

void RewriteText(std::istream& inputFile, std::ostream& outputFile)
{
    std::string line;
    
    while (!inputFile.eof())
    {
        getline(inputFile, line);

        outputFile << RemoveExtraSpacesFromStr(line) << std::endl;
    }
}

int main(int argc, char* argv[]) 
{
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }

    std::ifstream inputFile;
    std::ofstream outputFile;

    if (!OpenFiles(inputFile, outputFile, args->inputFileName, args->outputFileName))
    {
        return 1;
    }

    RewriteText(inputFile, outputFile);

    return 0;
}

