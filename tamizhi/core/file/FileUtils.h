#pragma once

#include <string>

/********************************************************************/

class crFilePath;
class crFileReader;

/********************************************************************/

namespace tmz
{

/////////////////////////////////////////////////
///    Utility function for file manipulation ///
/////////////////////////////////////////////////

// Read the contents from file.
bool loadFromFile(std::string& data, const crFilePath& filePath);
// Save the data to file.
bool saveToFile(const std::string& data, const crFilePath& filePath, bool append = false);

// Checks
bool isDir(const crFilePath& filePath);
bool isDir(const std::string& filePath);
bool isFile(const crFilePath& filePath);
bool isFile(const std::string& filePath);
bool isValid(const crFilePath& filePath);
bool isValid(const std::string& filePath);

} // namespace tmz
