#pragma once

#include <string>

namespace crUtils
{

// Comparision.
bool equals(const std::string& a, const std::string& b);
// Comparision(ignore case).
bool iequals(std::string a, std::string b);
// Check if string is empty.
bool empty(const std::string& str);

// Convert to lowercase letters.
std::string toLower(std::string a);
// Convert to upper case letters.
std::string toUpper(std::string a);
// Repeat string.
std::string repeat(const std::string& a, int n);
} // namespace crUtils
