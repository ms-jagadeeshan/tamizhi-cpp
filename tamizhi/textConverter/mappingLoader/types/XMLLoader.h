#pragma once

#include "tamizhi/core/base/Core.h"
#include "tamizhi/textConverter/mappingLoader/LoaderBase.h"

namespace tmz
{
class tcXMLLoader : public tcLoaderBase
{
    using BaseType = tcLoaderBase;

public:
    // Constructor.
    tcXMLLoader() = default;
    explicit tcXMLLoader(const crFilePath& file);
    ~tcXMLLoader() override = default;

private:
    // Implementation of reading the mapping.
    tmzSPCollection<tcMapping> readMappingInternal() override;
    // Actual Implementation of reading.
    tmzSPCollection<tcMapping> readMappingImpl(tinyxml2::XMLElement* rootElement);
    // Read the language element.
    tmzSPCollection<tcMapping> readLanguage(tinyxml2::XMLElement* langElement);
    // Read the encode element.
    tmzSPCollection<tcMapping> readEncode(tinyxml2::XMLElement* encodeElement, const std::string& langCode);
    // Read  the encodeToUnicode element.
    void readEncodeToUnicode(tinyxml2::XMLElement* encodeToUnicodeElement, tmzCollection<std::string>& from, tmzCollection<std::string>& to);
    // Read the unicodeToEncode element.
    void readUnicodeToEncode(tinyxml2::XMLElement* encodeToUnicodeElement, tmzCollection<std::string>& from, tmzCollection<std::string>& to);

    // Implementation of write the mapping.
    bool writeMappingInternal(const tmzSPCollection<tcMapping>& mapping, const crFilePath& file) override;

private:
    // Store the XMLDocument.
    tinyxml2::XMLDocument mDoc;
    // Store the XMLElement.
    tinyxml2::XMLElement* mRootElement;
    // Default max match length.
    static const int DEFAULT_MAX_MATCH_LENGTH = 4;
    // Default least character unit size(in bytes).
    static const int DEFAULT_LEAST_UNIT_SIZE = 1;
};

} // namespace tmz
