#include "tamizhi/textConverter/mapping/manager/MappingManager.h"
#include "tamizhi/textConverter/mapping/Mapping.h"
#include "tamizhi/textConverter/utils/ConversionType.h"
#include <algorithm>

/********************************************************************/

void tmz::tcMappingManager::registerMapping(const tmzSP<tmz::tcMapping>& mapping)
{
    registerMappingInternal(mapping);
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

tmzCollection<std::string> tmz::tcMappingManager::getLangList()
{
    tmzCollection<std::string> langs;
    std::transform(mLangMap.begin(), mLangMap.end(), std::back_inserter(langs), tmz::Lambdas::extractKey);
    return langs;
}

/********************************************************************/

tmzCollection<std::string> tmz::tcMappingManager::getEncodingList()
{
    tmzCollection<std::string> encodings;
    std::transform(mEncodeMap.begin(), mEncodeMap.end(), std::back_inserter(encodings), tmz::Lambdas::extractKey);
    return encodings;
}

/********************************************************************/

void tmz::tcMappingManager::registerMappingInternal(const tmzSP<tcMapping>& mapping)
{
    auto langCode = mapping->langCode();
    if (langCode.empty())
        langCode = "unknown";

    auto encodeName = mapping->encodeName();
    if (encodeName.empty())
        encodeName = "unknown";

    int index = static_cast<int>(mapping->mappingType());

    mLangMap[langCode][encodeName][index] = mapping;
    mEncodeMap[encodeName][index] = mapping;
}

/********************************************************************/

/********************************************************************/

/********************************************************************/

/********************************************************************/
