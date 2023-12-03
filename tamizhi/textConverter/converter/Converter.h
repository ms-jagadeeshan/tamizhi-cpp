#pragma once

#include "tamizhi/core/base/Core.h"
#include "tamizhi/textConverter/utils/ConversionType.h"

namespace tmz
{
class tcMappingManager;

class TextConverter
{
public:
    TextConverter(bool init = false);
    ~TextConverter();

    // Setters.
    void setEncoding(const std::string& encoding, tcConversionType conversionType = ENCODE_TO_UNICODE);

    void readConfig();

    // For api.
    std::string convert(const std::string& encoding, tcConversionType conversionType, const std::string& input);
    std::string convert(const std::string& encoding, tcConversionType conversionType, const crFilePath& file);
    // Should not be used in api.
    std::string convert(const std::string& input);
    std::string convert(const crFilePath& file);
    void convert(const crFilePath& inputFile, const crFilePath& outputFile);
    void convert(const std::string& encoding, tcConversionType conversionType, const crFilePath& inputFile, const crFilePath& outputFile);

    // Getters.
    // List of available encoding.
    tmzCollection<std::string> getAvailableEncoding();
    // Get the mapping manager.
    const tmzSP<tcMappingManager>& mappingManager();

private:
    // Store the mapping manager.
    tmzSP<tmz::tcMappingManager> mMappingManager;
    // Store the encoding name.
    std::string mEncoding;
    // Store the conversion type.
    tcConversionType mConversionType;
};

} // namespace tmz
