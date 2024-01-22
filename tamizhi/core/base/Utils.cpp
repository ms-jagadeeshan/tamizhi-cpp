#include "tamizhi/core/base/Utils.h"
#include <algorithm>

/********************************************************************/

bool crUtils::equals(const std::string& a, const std::string& b)
{
    return a.compare(b) == 0;
}

/********************************************************************/

bool crUtils::iequals(std::string a, std::string b)
{
    std::string a1 = a;
    std::string b1 = b;
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
    std::transform(b.begin(), b.end(), b.begin(), ::tolower);
    return a1.compare(b1) == 0;
}

/********************************************************************/

bool crUtils::empty(const std::string& str)
{
    return str.empty();
}

/********************************************************************/

std::string crUtils::toLower(std::string a)
{
    std::transform(a.begin(), a.end(), a.begin(), ::tolower);
    return a;
}

/********************************************************************/

std::string crUtils::toUpper(std::string a)
{
    std::transform(a.begin(), a.end(), a.begin(), ::toupper);
    return a;
}

/********************************************************************/

std::string crUtils::repeat(const std::string& a, int n)
{
    std::string b = "";
    for (auto i = 0; i < n; ++i)
    {
        b.append(a);
    }
    return b;
}

/********************************************************************/
