#include "Utils.h"


std::string StringToLowerCase(std::string const& url)
{
    std::string urlToLowerCase = url;
    std::transform(urlToLowerCase.begin(), urlToLowerCase.end(), urlToLowerCase.begin(), ::tolower);

    return urlToLowerCase;
}
