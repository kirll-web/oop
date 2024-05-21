
#include <iostream>
#include <fstream>
#include <optional>
#include <string>

const std::string LEFT = "L", RIGHT = "R";

struct Args
{
    std::string byte;
    std::string numberOfBits;
    std::string rotation;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "Usage: <byte> <number of bits> <L / R>\n";
        return std::nullopt;
    }

    Args args;
    args.byte = argv[1];
    args.numberOfBits = argv[2];
    args.rotation = argv[3];
    return args;
}


int RotationByte(int decNumber, int numberOfBits, const std::string& rotation) 
{
    int result;

    if (rotation == LEFT)
    {
        result = decNumber << numberOfBits;
        result = result & ~(~0 << 8);
        decNumber >>= 8 - numberOfBits;
        result = result | decNumber;
    }
    else if (rotation == RIGHT)
    {
        result = decNumber >> numberOfBits;
        decNumber <<= 8 - numberOfBits;
        decNumber = decNumber & ~(~0 << 8);
        result = result | decNumber;
    }

    return result;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    }

    int decNumber, numberOfBits;
    try 
    {
        decNumber = std::stoi(args->byte);
        numberOfBits = std::stoi(args->numberOfBits);
    } 
    catch (std::invalid_argument const& e) 
    {
        std::cout << "Error input byte";
        return 1;
    }
    catch (std::out_of_range const& e)
    {
        std::cout << "Integer overflow: std::out_of_range thrown" << std::endl;
        return 1;
    }
   

    int result;
    if (args->rotation == LEFT || args->rotation == RIGHT) 
    {
        result = RotationByte(decNumber, numberOfBits, args->rotation);
    } 
    else
    {
        std::cout << "Error input rotation";
        return 1;
    }

    std::cout << "result: " << result << " ";

    return 0;
}



