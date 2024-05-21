#include "RemoveExtraSpacesFromStr.h"

std::string RemoveExtraSpacesBeforeStrAndReverse(std::string const& str)
{
    int it = 0;
    std::string result = str;

    while (it < str.length() && str[it] == ' ')
    {
        it++;
    }

    if (it > 0)
    {
        result = result.substr(it, str.length() - 1);
    }
    reverse(result.begin(), result.end());

    return result;
}

std::string RemoveExtraSpacesBeforeAndAfterStr(std::string const& str)
{
    std::string result = str;

    for (int i = 0; i < 2; i++)
    {
        result = RemoveExtraSpacesBeforeStrAndReverse(result);
    }

    return result;
}

std::string RemoveExtraSpacesMiddleStr(std::string const& str) {
    std::string result = str;
    int it = 0;
    char prevCh;
    if (it < result.length())
    {
        prevCh = result[it];
        it++;
    }

    while (it < result.length())
    {
        //advice: использовать erase вместо substring
        if (result[it] == ' ' && prevCh == ' ')
        {
            std::string beforeIt = result.substr(0, it);
            std::string afterIt = result.substr(it + 1, result.length() - 1);;
            result = beforeIt + afterIt;
            it--;
        }
        prevCh = result[it];
        it++;
    }

    return result;
}

std::string RemoveExtraSpacesFromStr(std::string const& str)
{
    std::string result;

    result = RemoveExtraSpacesBeforeAndAfterStr(str);

    result = RemoveExtraSpacesMiddleStr(result);

    return result;
}