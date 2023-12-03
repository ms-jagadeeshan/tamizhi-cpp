#pragma once

#include "tamizhi/core/base/Macros.h"
#include "tamizhi/core/file/ConfigPath.h"
#include <filesystem>
#include <string>

class crFilePath
{

public:
    explicit crFilePath(const std::string& path = "");
    explicit crFilePath(const char* path = "");

    // Setters.
    void setFileName(const std::string& fileName);
    // Set extension of the file.
    void setExtension(const std::string& ext);
    // Set the prefix of the file.
    void setPrefix(const std::string& prefix);
    // Set the suffix of the file.
    void setSuffix(const std::string& suffix);

    // Getters.
    // Get the absolute path of the file.
    std::string get() const;
    // Get the file name.
    std::string getFileName() const;
    // Get only extension.
    std::string getExtension() const;

    // Check if the path is valid.
    bool isValid() const;
    // Check if the path is directory.
    bool isDir() const;
    // Check if the path is file.
    bool isFile() const;
    // Print all the values.
    void print();

private:
    // Resolve the file name into parts.
    void resolveFileName(const std::string& fileName);
    // Parse Path into sub parts.
    void parsePath(const std::string& path);
    // Get the modifier path.
    std::string getModifierPath(const std::string& modifier);

public:
    inline static char mSlash = std::filesystem::path::preferred_separator;
    inline static std::string mFilePathData = PROJECT_DIR_DATA;
    inline static std::string mFilePathLog = PROJECT_DIR_LOG;

private:
    // Store the path.
    std::filesystem::path mPath;
    // File name without prefix, suffix and extension.
    std::string mStem;
    // Relative file name.
    std::string mFileName;
    // Absolute parent path.
    std::string mFilePath;
    // File extension.
    std::string mExtension;
    // File prefix.
    std::string mPrefix;
    // File suffix.
    std::string mSuffix;
};
