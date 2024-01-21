#pragma once

#include "tamizhi/core/base/Core.h"
#include "tamizhi/textConverter/utils/ConversionType.h"
#include "textConverter/api/RESTInterface.h"
#include "textConverter/mapping/manager/MappingManager.h"

namespace tmz
{
class TextConverter
{
public:
    TextConverter(bool initRest = true);
    ~TextConverter();

    // Setters.
    void setEncoding(const std::string& encoding, tcConversionType conversionType = ENCODE_TO_UNICODE);
    void initRestInterface(bool initRest = true);

    void loadFromFile(const crFilePath& filePath);
    void loadFromString(const std::string& mappingString, const std::string& fileType);

    // For api.
    // Encoding, conversion type, inputdata(string)
    std::string convert(const std::string& encoding, tcConversionType conversionType, const std::string& inputData) const;
    // Encoding, conversion type, inputFile
    std::string convert(const std::string& encoding, tcConversionType conversionType, const crFilePath& inputFile) const;
    // mapping string, encoding, mapping filetype, conversion type, input data
    std::string convert(const std::string& mappingString, const std::string& encoding, const std::string& fileType, tcConversionType conversionType, const std::string& inputData) const;
    // Should not be used in api.
    std::string convert(const std::string& inputData) const;
    std::string convert(const crFilePath& inputFile) const;
    void convert(const crFilePath& inputFile, const crFilePath& outputFile) const;
    void convert(const std::string& encoding, tcConversionType conversionType, const crFilePath& inputFile, const crFilePath& outputFile) const;

    // Getters.
    // List of available encoding.
    tmzCollection<std::string> getAvailableEncoding() const;
    // Get the mapping manager.
    const tmzRP<tcMappingManager> mappingManager() const;

private:
    // Store the mapping manager.
    tmz::tcMappingManager mMappingManager;
    // Store the encoding name.
    std::string mEncoding;
    // Store the conversion type.
    tcConversionType mConversionType;
    // Store the rest interface.
    tmzSP<tcRestInterface> mRestInterface;
};

} // namespace tmz
