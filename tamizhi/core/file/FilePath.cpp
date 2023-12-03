#include "tamizhi/core/file/FilePath.h"
#include "tamizhi/core/file/FileUtils.h"

/********************************************************************/

crFilePath::crFilePath(const std::string& path)
{
    setFileName(path);
}

/********************************************************************/

crFilePath::crFilePath(const char* path)
{
    setFileName(std::string(path));
}

/********************************************************************/

void crFilePath::setFileName(const std::string& fileName)
{
    resolveFileName(fileName);
}

/********************************************************************/

void crFilePath::setExtension(const std::string& ext)
{
    mExtension = ext;
}
/********************************************************************/

void crFilePath::setPrefix(const std::string& prefix)
{
    mPrefix = prefix;
}

/********************************************************************/

void crFilePath::setSuffix(const std::string& suffix)
{
    mSuffix = suffix;
}

/********************************************************************/

std::string crFilePath::get() const
{
    return (mFilePath + getFileName());
}

/********************************************************************/

std::string crFilePath::getFileName() const
{
    return (mPrefix + mStem + mSuffix + mExtension);
}

/********************************************************************/

std::string crFilePath::getExtension() const
{
    // Extension is designed to have the '.' in it.
    // So when we return we remove this dot.
    if (mExtension == "")
        return "";
    else
        return mExtension.substr(1);
}

/********************************************************************/

bool crFilePath::isValid() const
{
    return tmz::isValid(this->get());
}

/********************************************************************/

bool crFilePath::isDir() const
{
    return tmz::isDir(this->get());
}

/********************************************************************/

bool crFilePath::isFile() const
{
    return tmz::isFile(this->get());
}

/********************************************************************/

void crFilePath::print()
{
    tmzPrint("path.get() : %s\n", get().c_str());
    tmzPrint("mPath: %s\n", mPath.string().c_str());
    tmzPrint("mStem: %s\n", mStem.c_str());
    tmzPrint("mFileName: %s\n", mFileName.c_str());
    tmzPrint("mFilePath: %s\n", mFilePath.c_str());
    tmzPrint("mExtension: %s\n", mExtension.c_str());
    tmzPrint("mPrefix: %s\n", mPrefix.c_str());
    tmzPrint("mSuffix: %s\n", mSuffix.c_str());
}

/********************************************************************/

void crFilePath::resolveFileName(const std::string& fileName)
{
    checkAndReturn(!fileName.empty(), "");
    auto customPath = fileName.find("://");
    std::string path = fileName;
    std::string modifier = "";

    if (customPath != std::string::npos)
    {
        modifier = fileName.substr(0, customPath);
        path = fileName.substr(customPath + 3);
    }
    // If there is a ~ , then modifier is ignored.
    if (path[0] == '~')
        path = std::string(getenv("HOME")) + fileName.substr(1);
    else if (!modifier.empty())
        path = getModifierPath(modifier) + path;

    parsePath(path);
}

/********************************************************************/

void crFilePath::parsePath(const std::string& path)
{
    mPath = std::filesystem::absolute(path).lexically_normal();
    mFilePath = mPath.parent_path().string() + mSlash;
    mFileName = mPath.filename().string();
    mStem = mPath.stem().string();
    mExtension = mPath.extension().string();
}

/********************************************************************/

std::string crFilePath::getModifierPath(const std::string& modifier)
{
    if (crUtils::iequals(modifier, "data"))
        return mFilePathData + mSlash;
    else if (crUtils::iequals(modifier, "log"))
        return mFilePathLog + mSlash;
    else
        return "";
}

/********************************************************************/
