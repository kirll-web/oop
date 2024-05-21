#include <iostream>
#include <string>
#include <optional>
#include <thread>
#include "GeneratePrimeNumbersFunc.h"

const int MAX_SIZE = 100'000'000, MIN_SIZE = 2;

struct Args
{
    int upperBound;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: GeneratePrimeNumbers.exe <upperBound>\n";
        return std::nullopt;
    }

    Args args;

    try
    {
        args.upperBound = std::stoi(argv[1]);
    }
    catch (std::invalid_argument const& )
    {
        std::cout << "Error input upperBound";
        return std::nullopt;
    }
    catch (std::out_of_range const& )
    {
        std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
        return std::nullopt;
    }
    catch (std::string const& e)
    {
        std::cout << "Error " <<  e << std::endl;
        return std::nullopt;
    }
    //проверить на то, что аргумент полностью числовой
    return args;
}

void OutputPrimeNumbers(std::set<int> const & numbers)
{
    for (int n : numbers)
    {
        std::cout << n << "\t";
    }
}

bool CheckNumberBoundaries(int upperBound)
{
    if (upperBound > MAX_SIZE)
    {
        std::cout << "The entered number is greater than the maximum size." << std::endl;
        return false;
    }
    else if (upperBound < MIN_SIZE)
    {
        std::cout << "There are no prime numbers for the entered number." << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }
    
    if (!CheckNumberBoundaries(args->upperBound))
    {
        return 1;
    }
   
    auto start = std::chrono::high_resolution_clock::now();
    
    std::set<int> numbers = GeneratePrimeNumbersSet(args->upperBound);
    
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<float> duration= end - start;

    std::cout << std::endl << duration.count() << "\t" << numbers.size() << std::endl;

    OutputPrimeNumbers(numbers);

    return 0;
}

