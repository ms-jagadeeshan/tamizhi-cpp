#include "tamizhi/core/base/Utils.h"
#include <algorithm>

bool crUtils::equals(const std::string& a, const std::string& b)
{
    return a.compare(b) == 0;
}

/********************************************************************/

bool crUtils::iequals(const std::string& a, const std::string& b)
{
    std::string a1 = a;
    std::string b1 = b;
    std::transform(a1.begin(), a1.end(), a1.begin(), ::tolower);
    std::transform(b1.begin(), b1.end(), b1.begin(), ::tolower);
    return a1.compare(b1) == 0;
}

/********************************************************************/

bool crUtils::empty(const std::string& str)
{
    return str.empty();
}

/********************************************************************/
