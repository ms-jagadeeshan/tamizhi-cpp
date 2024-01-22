#include "tamizhi/textConverter/converter/Converter.h"
#include "tamizhi/textConverter/mapping/Mapping.h"
#include "tamizhi/textConverter/mapping/manager/MappingManager.h"
#include "tamizhi/textConverter/mappingLoader/MappingLoader.h"

/********************************************************************/

tmz::TextConverter::TextConverter(bool initRest)
{
    this->initRestInterface(initRest);
}

/********************************************************************/

tmz::TextConverter::~TextConverter()
{
}

/********************************************************************/

void tmz::TextConverter::setEncoding(const std::string& encoding, tcConversionType conversionType)
{
    mEncoding = encoding;
    mConversionType = conversionType;
}

void tmz::TextConverter::initRestInterface(bool initRest)
{
    if (initRest)
    {
        mRestInterface = std::make_shared<tcRestInterface>(crRawPointer(this));
        mRestInterface->init();
        mRestInterface->start();
    }
}

/********************************************************************/

void tmz::TextConverter::loadFromFile(const crFilePath& filePath)
{
    auto mappings = tmz::tcMappingLoader::read(filePath);
    mMappingManager.registerMapping(mappings);
}

/********************************************************************/

void tmz::TextConverter::loadFromString(const std::string& mappingString, const std::string& fileType)
{
    auto mappings = tmz::tcMappingLoader::readFromString(mappingString, fileType);
    mMappingManager.registerMapping(mappings);
}

/********************************************************************/

std::string tmz::TextConverter::convert(const std::string& encoding, tcConversionType conversionType, const std::string& inputData) const
{
    auto mapping = mMappingManager.getMapping(encoding, conversionType);
    checkAndReturnValue(mapping != nullptr, "[Text Converter] Mapping not found", "");
    return mapping->convert(inputData);
}

/********************************************************************/

std::string tmz::TextConverter::convert(const std::string& encoding, tcConversionType conversionType, const crFilePath& inputFile) const
{
    auto mapping = mMappingManager.getMapping(encoding, conversionType);
    checkAndReturnValue(mapping != nullptr, "[Text Converter] Mapping not found", "");
    std::string inputData;
    tmz::loadFromFile(inputData, inputFile);
    return mapping->convert(inputData);
}

/********************************************************************/

std::string tmz::TextConverter::convert(const std::string& mappingString, const std::string& encoding, const std::string& fileType, tcConversionType conversionType, const std::string& inputData) const
{
    auto mappings = tmz::tcMappingLoader::readFromString(mappingString, fileType);
    for (auto mapping : mappings)
    {
        if (mapping->encodeName() == encoding && mapping->mappingType() == conversionType)
            return mapping->convert(inputData);
    }
    return "";
}

/********************************************************************/

std::string tmz::TextConverter::convert(const std::string& inputData) const
{
    return convert(mEncoding, mConversionType, inputData);
}

/********************************************************************/

std::string tmz::TextConverter::convert(const crFilePath& inputFile) const
{
    return convert(mEncoding, mConversionType, inputFile);
}

/********************************************************************/

void tmz::TextConverter::convert(const crFilePath& inputFile, const crFilePath& outputFile) const
{
    convert(mEncoding, mConversionType, inputFile, outputFile);
}

/********************************************************************/

void tmz::TextConverter::convert(const std::string& encoding, tcConversionType conversionType, const crFilePath& inputFile, const crFilePath& outputFile) const
{
    auto result = convert(inputFile);
    checkAndReturn(!result.empty(), "");
    tmz::saveToFile(result, outputFile);
}

/********************************************************************/

tmzCollection<std::string> tmz::TextConverter::getAvailableEncoding() const
{
    return mMappingManager.getEncodingList();
}

/********************************************************************/

const tmzRP<tmz::tcMappingManager> tmz::TextConverter::mappingManager() const
{
    return crRawPointer(&mMappingManager);
}

/********************************************************************/
