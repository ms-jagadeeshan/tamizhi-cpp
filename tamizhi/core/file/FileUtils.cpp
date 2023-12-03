#include "core/file/FileUtils.h"

#include <filesystem>
#include <fstream>

#include "core/file/FilePath.h"
#include "core/file/FileReader.h"

/************************************************************************************/

bool tmz::loadFromFile(std::string& data, const crFilePath& filePath)
{
    try
    {
        std::string msg = "Could not open file" + filePath.get();
        checkAndReturnValue(filePath.isValid(), msg.c_str(), false);
        std::ifstream in(filePath.get().c_str(), std::ios::in);
        checkAndReturnValue(in, msg.c_str(), false);
        std::ostringstream contents;
        contents << in.rdbuf();
        data = contents.str();
        if (in.is_open())
        {
            in.close();
        }
        return true;
    }
    catch (const std::ifstream::failure& e)
    {
        tmzError("File not found: %s", filePath.get().c_str());
        return false;
    }
}

/************************************************************************************/

bool tmz::saveToFile(const std::string& data, const crFilePath& filePath, bool append)
{
    std::ofstream out;
    if (append)
        out = std::ofstream(filePath.get().c_str(), std::ios::out | std::ios::app);
    else
        out = std::ofstream(filePath.get().c_str(), std::ios::out);

    std::string message = "Could not write file" + filePath.get();
    checkAndReturnValue(out, message.c_str(), false);
    out << data;
    if (out.is_open())
        out.close();
    return true;
}
/************************************************************************************/

bool tmz::isDir(const crFilePath& filePath)
{
    return std::filesystem::is_directory(filePath.get());
}

/************************************************************************************/

bool tmz::isDir(const std::string& filePath)
{
    return std::filesystem::is_directory(filePath);
}
/************************************************************************************/

bool tmz::isFile(const crFilePath& filePath)
{
    return std::filesystem::is_regular_file(filePath.get());
}

/************************************************************************************/

bool tmz::isFile(const std::string& filePath)
{
    return std::filesystem::is_regular_file(filePath);
}

/************************************************************************************/

bool tmz::isValid(const crFilePath& filePath)
{
    return std::filesystem::exists(filePath.get());
}

/************************************************************************************/

bool tmz::isValid(const std::string& filePath)
{
    return std::filesystem::exists(filePath);
}

/************************************************************************************/
