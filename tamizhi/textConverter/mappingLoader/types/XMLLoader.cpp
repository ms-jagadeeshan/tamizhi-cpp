#include "tamizhi/textConverter/mappingLoader/types/XMLLoader.h"

/********************************************************************/

tmz::tcXMLLoader::tcXMLLoader(const crFilePath& file)
    : BaseType(file)
{
}

/********************************************************************/

tmzSPCollection<tmz::tcMapping> tmz::tcXMLLoader::readMappingInternal()
{
    if (mData.empty())
    {
        auto success = mDoc.LoadFile(mFilePath.get().c_str());
        checkAndReturnValue(success == tinyxml2::XML_SUCCESS, std::string("Unable to parse the file" + mFilePath.get()).c_str(), {});
    }
    else
    {
        auto success = mDoc.Parse(mData.c_str(), mData.size());
        checkAndReturnValue(success == tinyxml2::XML_SUCCESS, "Unable ot parse the data", {});
    }

    mRootElement = mDoc.RootElement();
    return readMappingImpl(mRootElement);
}

/********************************************************************/

tmzSPCollection<tmz::tcMapping> tmz::tcXMLLoader::readMappingImpl(tinyxml2::XMLElement* rootElement)
{
    checkAndReturnValue(rootElement != nullptr, "[XML Loader] Root element is empty", {});

    tmzSPCollection<tmz::tcMapping> result;
    for (tinyxml2::XMLElement* langElement = rootElement->FirstChildElement("language");
         langElement != nullptr; langElement = langElement->NextSiblingElement("language"))
    {
        auto mappingCollection = readLanguage(langElement);
        result.insert(result.end(), mappingCollection.begin(), mappingCollection.end());
    }

    return result;
}

/********************************************************************/

tmzSPCollection<tmz::tcMapping> tmz::tcXMLLoader::readLanguage(tinyxml2::XMLElement* langElement)
{
    checkAndReturnValue(langElement != nullptr, "[XML Loader] Language element is empty", {});
    const char* langCode = langElement->Attribute("code");
    if (!langCode)
        langCode = "unknown";

    std::string langCodeStr = std::string(langCode);
    tmzSPCollection<tmz::tcMapping> result;

    for (tinyxml2::XMLElement* encodeElement = langElement->FirstChildElement("encode");
         encodeElement != nullptr; encodeElement = encodeElement->NextSiblingElement("encode"))
    {
        auto mappingCollection = readEncode(encodeElement, langCodeStr);
        result.insert(result.end(), mappingCollection.begin(), mappingCollection.end());
    }

    return result;
}

/********************************************************************/

tmzSPCollection<tmz::tcMapping> tmz::tcXMLLoader::readEncode(tinyxml2::XMLElement* encodeElement, const std::string& langCode)
{
    checkAndReturnValue(encodeElement != nullptr, "[XML Loader] Encode element is empty", {});

    int unicodeToEncodeMML = encodeElement->IntAttribute("unicodeToEncodeMML", DEFAULT_MAX_MATCH_LENGTH);
    int encodeToUnicodeMML = encodeElement->IntAttribute("encodeToUnicodeMML", DEFAULT_MAX_MATCH_LENGTH);
    int gcdCharSize = encodeElement->IntAttribute("gcdCharSize", DEFAULT_LEAST_UNIT_SIZE);
    const char* name = encodeElement->Attribute("name");

    tmzSP<tmz::tcMapping> encodeToUnicode = std::make_shared<tmz::tcMapping>(name, langCode, ENCODE_TO_UNICODE);
    encodeToUnicode->maxMatchLength(encodeToUnicodeMML);
    encodeToUnicode->gcdCharSize(gcdCharSize);
    tmzSP<tmz::tcMapping> unicodeToEncode = std::make_shared<tmz::tcMapping>(name, langCode, UNICODE_TO_ENCODE);
    unicodeToEncode->maxMatchLength(unicodeToEncodeMML);
    unicodeToEncode->gcdCharSize(gcdCharSize);

    tmzCollection<std::string> e2uFrom, u2eFrom, e2uTo, u2eTo;

    for (tinyxml2::XMLElement* e2uElement = encodeElement->FirstChildElement("encodeToUnicode");
         e2uElement != nullptr; e2uElement = e2uElement->NextSiblingElement("encodeToUnicode"))
        readEncodeToUnicode(e2uElement, e2uFrom, e2uTo);

    for (tinyxml2::XMLElement* u2eElement = encodeElement->FirstChildElement("unicodeToEncode");
         u2eElement != nullptr; u2eElement = u2eElement->NextSiblingElement("unicodeToEncode"))
        readUnicodeToEncode(u2eElement, u2eFrom, u2eTo);

    if (e2uFrom.empty())
    {
        encodeToUnicode->insert(u2eTo, u2eFrom);
        unicodeToEncode->insert(u2eFrom, u2eTo);
    }
    else if (u2eFrom.empty())
    {
        encodeToUnicode->insert(e2uFrom, e2uTo);
        unicodeToEncode->insert(e2uTo, e2uFrom);
    }
    else
    {
        encodeToUnicode->insert(e2uFrom, e2uTo);
        unicodeToEncode->insert(u2eFrom, u2eTo);
    }

    return {encodeToUnicode, unicodeToEncode};
}

/********************************************************************/

void tmz::tcXMLLoader::readEncodeToUnicode(tinyxml2::XMLElement* encodeToUnicodeElement, tmzCollection<std::string>& from, tmzCollection<std::string>& to)
{
    checkAndReturn(encodeToUnicodeElement != nullptr, "[XML Loader] EncodeToUnicode element is empty");

    const char* from_elem = encodeToUnicodeElement->Attribute("from");
    const char* to_elem = encodeToUnicodeElement->Attribute("to");

    if (from_elem != nullptr && to_elem != nullptr)
    {
        from.emplace_back(from_elem);
        to.emplace_back(to_elem);
    }
}

/********************************************************************/

void tmz::tcXMLLoader::readUnicodeToEncode(tinyxml2::XMLElement* unicodeToEncodeElement, tmzCollection<std::string>& from, tmzCollection<std::string>& to)
{
    checkAndReturn(unicodeToEncodeElement != nullptr, "[XML Loader] EncodeToUnicode element is empty");

    const char* from_elem = unicodeToEncodeElement->Attribute("from");
    const char* to_elem = unicodeToEncodeElement->Attribute("to");

    if (from_elem != nullptr && to_elem != nullptr)
    {
        from.emplace_back(from_elem);
        to.emplace_back(to_elem);
    }
}
/********************************************************************/

bool tmz::tcXMLLoader::writeMappingInternal(const tmzSPCollection<tmz::tcMapping>& mapping, const crFilePath& file)
{
    return false;
}

/********************************************************************/
