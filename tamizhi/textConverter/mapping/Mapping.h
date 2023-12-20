#pragma once

#include "tamizhi/core/base/Core.h"
#include "tamizhi/textConverter/utils/ConversionType.h"

namespace tmz
{
class tcMappingManager;
class tcMapping
{
    friend tcMappingManager;
    using tmzEUMap = tmzUOMap<std::string, std::string>;

public:
    // Constructor.
    tcMapping(const std::string& encodeName = "", const std::string& langCode = "", tcConversionType mappingType = ENCODE_TO_UNICODE);
    ~tcMapping() = default;

    // Setters.
    // Set the language code.
    void langCode(const std::string& langCode);
    // Set the encoding name.
    void encodeName(const std::string& encodeName);
    // Set the mapping type.
    void mappingType(tcConversionType mappingType);
    // Set if the mapping is encode to Unicode.
    void setEncodeToUnicode(bool isEncodeToUnicode = true);
    // Set the max match length.
    void maxMatchLength(int maxMatchLength);
    // Set the gcd of character size.
    void gcdCharSize(int gcdCharSize);
    // Insert the element to the mapping.
    bool insert(std::string key, std::string value);
    // Insert the element from vector of keys and vector of values.
    bool insert(const tmzCollection<std::string>& keys, const tmzCollection<std::string>& values);

    // Apply the mappings to the string.
    std::string convert(const std::string& input);

    // Getters.
    // Get the language code.
    std::string langCode();
    // Get the encoding name.
    std::string encodeName();
    // Get the mapping.
    const tmzSP<tmzEUMap>& mapping();
    // Get if the mapping is encode to Unicode.
    bool isEncodeToUnicode();
    // Get the mapping type.
    tcConversionType mappingType();
    // Get the max match length.
    std::size_t maxMatchLength();
    // Get the gcd of character size.
    std::size_t gcdCharSize();
    // Print the mapping.
    void print();

private:
    void replaceAll(std::string& str, const std::string& from, const std::string& to);

private:
    // Store the Unique id.
    int mUuid;
    // Store the language code.
    std::string mLangCode = "";
    // Store the encoding Name.
    std::string mEncodeName = "";
    // Store the type of mapping.
    tcConversionType mMappingType = ENCODE_TO_UNICODE;
    // Maximum match lenght.
    std::size_t mMaxMatchLength = 4;
    // Least character unit size in the mapping.
    std::size_t mGcdCharSize = 1;
    // Mapping from encoding to unicode.
    tmzSP<tmzEUMap> mMapping = std::make_shared<tmzEUMap>();
};

} // namespace tmz

using tmzEUMap = tmzUOMap<std::string, std::string>;
