#include "tamizhi/textConverter/converter/Converter.h"
#include "tamizhi/textConverter/mapping/Mapping.h"
#include "tamizhi/textConverter/mapping/manager/MappingManager.h"

/********************************************************************/

tmz::TextConverter::TextConverter(bool init)
{
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

/********************************************************************/

std::string tmz::TextConverter::convert(const std::string& encoding, tcConversionType conversionType, const std::string& input)
{
    auto mapping = mMappingManager->getMapping(encoding, conversionType);
    checkAndReturnValue(mapping != nullptr, "[Text Converter] Mapping not found", "");
    return mapping->convert(input);
}

/********************************************************************/

std::string tmz::TextConverter::convert(const std::string& encoding, tcConversionType conversionType, const crFilePath& input)
{

    return "";
}

/********************************************************************/

std::string tmz::TextConverter::convert(const std::string& input)
{
    return convert(mEncoding, mConversionType, input);
}

/********************************************************************/

std::string tmz::TextConverter::convert(const crFilePath& file)
{
    return convert(mEncoding, mConversionType, file);
}

/********************************************************************/

void tmz::TextConverter::convert(const crFilePath& inputFile, const crFilePath& outputFile)
{
    convert(mEncoding, mConversionType, inputFile, outputFile);
}

/********************************************************************/

void tmz::TextConverter::convert(const std::string& encoding, tcConversionType conversionType, const crFilePath& inputFile, const crFilePath& outputFile)
{
    auto result = convert(inputFile);
    checkAndReturn(!result.empty(), "");
    tmz::saveToFile(result, outputFile);
}

/********************************************************************/

tmzCollection<std::string> tmz::TextConverter::getAvailableEncoding()
{
    return mMappingManager->getEncodingList();
}

/********************************************************************/

const tmzSP<tmz::tcMappingManager>& tmz::TextConverter::mappingManager()
{
    return mMappingManager;
}

/********************************************************************/
