#pragma once

#include <string>

namespace crUtils
{

// Comparision.
bool equals(const std::string& a, const std::string& b);
// Comparision(ignore case).
bool iequals(const std::string& a, const std::string& b);
// Check if string is empty.
bool empty(const std::string& str);

} // namespace crUtils
