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

bool tmz::tcXMLLoader::writeMappingInternal(const tmzSPCollection<tmz::tcMapping>& mappings, const crFilePath& file)
{
    tmzMap<std::string, tmzMap<std::string, tmzArray<tmzSP<tcMapping>, 2>>> langMap;
    for (auto& mapping : mappings)
    {
        auto langCode = mapping->langCode();
        if (langCode.empty())
            langCode = "unknown";

        auto encodeName = mapping->encodeName();
        if (encodeName.empty())
            encodeName = "unknown";

        int index = static_cast<int>(mapping->mappingType());
        langMap[langCode][encodeName][index] = mapping;
    }
    tinyxml2::XMLDocument xmlDoc;
    tinyxml2::XMLElement* rootElement = xmlDoc.NewElement("root");
    xmlDoc.InsertFirstChild(rootElement);

    for (const auto& [langCode, encodeMap] : langMap)
    {
        tinyxml2::XMLElement* langElement = xmlDoc.NewElement("language");
        langElement->SetAttribute("code", langCode.c_str());
        rootElement->InsertEndChild(langElement);
        for (const auto& [encodeName, encodeArray] : encodeMap)
        {
            tinyxml2::XMLElement* encodeElement = xmlDoc.NewElement("encode");
            encodeElement->SetAttribute("name", encodeName.c_str());
            langElement->InsertFirstChild(encodeElement);

            auto e2uMapping = encodeArray[ENCODE_TO_UNICODE];
            if (e2uMapping != nullptr)
            {
                encodeElement->SetAttribute("encodeToUnicodeMML", e2uMapping->maxMatchLength());
                encodeElement->SetAttribute("gcdCharSize", e2uMapping->gcdCharSize());
                for (const auto& [from, to] : *e2uMapping->mapping())
                {
                    tinyxml2::XMLElement* e2uElement = xmlDoc.NewElement("encodeToUnicode");
                    e2uElement->SetAttribute("from", from.c_str());
                    e2uElement->SetAttribute("to", to.c_str());
                    encodeElement->InsertEndChild(e2uElement);
                }
            }

            auto u2eMapping = encodeArray[UNICODE_TO_ENCODE];
            if (u2eMapping != nullptr)
            {
                encodeElement->SetAttribute("unicodeToEncodeMML", u2eMapping->maxMatchLength());
                encodeElement->SetAttribute("gcdCharSize", u2eMapping->gcdCharSize());
                for (const auto& [from, to] : *u2eMapping->mapping())
                {
                    tinyxml2::XMLElement* u2eElement = xmlDoc.NewElement("unicodeToEncode");
                    u2eElement->SetAttribute("from", from.c_str());
                    u2eElement->SetAttribute("to", to.c_str());
                    encodeElement->InsertEndChild(u2eElement);
                }
            }
        }
    }

    return xmlDoc.SaveFile(file.get().c_str()) == tinyxml2::XML_SUCCESS;
}

/********************************************************************/
