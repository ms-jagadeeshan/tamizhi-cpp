#include "tamizhi/textConverter/mapping/manager/MappingManager.h"
#include "tamizhi/textConverter/mapping/Mapping.h"
#include "tamizhi/textConverter/utils/ConversionType.h"
#include <algorithm>

/********************************************************************/

void tmz::tcMappingManager::registerMapping(const tmzCollection<tmzSP<tmz::tcMapping>>& mappings)
{
    const auto& ref = getInstance();
    for (auto& mapping : mappings)
    {
        ref->registerMapping(mapping);
    }
}

/********************************************************************/

void tmz::tcMappingManager::registerMapping(const tmzSP<tmz::tcMapping>& mapping)
{
    const auto& ref = getInstance();
    ref->registerMappingInternal(mapping);
}

/********************************************************************/

void tmz::tcMappingManager::unregisterMapping(const tmzSP<tmz::tcMapping>& mapping)
{
}

/********************************************************************/

void tmz::tcMappingManager::unregisterMapping(const std::string& encodeName, tcConversionType mappingType)
{
}

/********************************************************************/

tmzCollection<std::string> tmz::tcMappingManager::getLangList() const
{
    const auto& ref = getInstance();
    tmzCollection<std::string> langs;
    std::transform(ref->mLangMap.begin(), ref->mLangMap.end(), std::back_inserter(langs), tmz::Lambdas::extractKey);
    return langs;
}

/********************************************************************/

tmzCollection<std::string> tmz::tcMappingManager::getEncodingList(const std::string& langCode) const
{
    const auto& ref = getInstance();
    tmzCollection<std::string> encodings;
    if (langCode == "")
        std::transform(ref->mEncodeMap.begin(), ref->mEncodeMap.end(), std::back_inserter(encodings), tmz::Lambdas::extractKey);
    else
    {
        auto it = ref->mLangMap.find(langCode);
        if (it != ref->mLangMap.end())
            std::transform(it->second.begin(), it->second.end(), std::back_inserter(encodings), tmz::Lambdas::extractKey);
    }
    return encodings;
}

/********************************************************************/

const tmzSP<tmz::tcMapping>& tmz::tcMappingManager::getMapping(const std::string& encodeName, tcConversionType mappingType) const
{
    const auto& ref = getInstance();
    return ref->mEncodeMap[encodeName][mappingType];
}

/********************************************************************/

void tmz::tcMappingManager::registerMappingInternal(const tmzSP<tcMapping>& mapping)
{
    const auto& ref = getInstance();
    auto langCode = mapping->langCode();
    if (langCode.empty())
        langCode = "unknown";

    auto encodeName = mapping->encodeName();
    if (encodeName.empty())
        encodeName = "unknown";

    int index = static_cast<int>(mapping->mappingType());

    ref->mLangMap[langCode][encodeName][index] = mapping;
    ref->mEncodeMap[encodeName][index] = mapping;
}

/********************************************************************/

/********************************************************************/

/********************************************************************/

/********************************************************************/
