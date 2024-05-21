#include <iostream>
#include <string>
#include <optional>
#include <map>
#include <vector>
#include <locale.h>
#include <locale>
#include <Windows.h>
#include "temp.h"

const int ALF_SIZE = 3;

struct Args
{
    std::string inputFileName;
    std::string outputFileName;
    std::map<std::string, std::string> params;
};

struct bohr_vrtx {
    int next_vrtx[ALF_SIZE], pat_num;
    bool flag;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc < 5 || argc % 2 == 0)
    {
        std::cout << "Invalid arguments count\n";
        std::cout << "expand_template.exe <input-file> <output-file> [<param> <value> [<param> <value> …]]\n";
        return std::nullopt;
    }

    Args args;

    args.inputFileName = argv[1];
    args.outputFileName = argv[2];

    for (int i = 3; i < argc; i+=2)
    {
        args.params[argv[i]] = argv[i + 1];
    }

    return args;
}

void InitLocale()
{
    std::locale rus("russian");// вынести в отдельную процедуру
    std::locale::global(rus);
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

std::string ExpandTemplate(std::string const& tpl, std::map<std::string, std::string> const& params)
{
    std::string tempStr = tpl;

    auto it = params.find("asd");


}

int main(int argc, char* argv[])
{
    InitLocale();
    auto args = ParseArgs(argc, argv);

    if (!args)
    {
        return 1;
    } 

    std::string const tpl = "-AABBCCCCCABC+";
    std::map<std::string, std::string> params;
    params["A"] = "[a]";
    params["AA"] = "[aa]";
    params["B"] = "[b]";
    params["BB"] = "[bb]";
    params["C"] = "[c]";
    params["CC"] = "[cc]";

  

    

    return 0;
}



//———Вывод
//for (auto it = args->params.begin(); it != args->params.end(); ++it)
//{
//    std::cout << it->first << "\t" << it->second << std::endl;
//}

//+
//
//for (const auto& [product, price] : params)
//{
//    std::cout << product << " " << price << " " << "\n";
//}