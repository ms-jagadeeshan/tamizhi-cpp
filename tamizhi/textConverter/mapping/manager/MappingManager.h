#pragma once

#include "tamizhi/core/base/Core.h"
#include "tamizhi/core/base/Singleton.h"
#include "tamizhi/textConverter/utils/ConversionType.h"

namespace tmz
{
class tcMapping;

class tcMappingManager : public crSingleton<tcMappingManager>
{
    TMZ_AUTO_SINGLETON(tcMappingManager);

public:
    tcMappingManager();
    ~tcMappingManager();

    // Register mapping to mapping manager.
    void registerMapping(const tmzSP<tcMapping>& mapping);
    // De-register mapping from mapping manager.
    void unregisterMapping(const tmzSP<tcMapping>& mapping);
    void unregisterMapping(const std::string& encodeName, tcConversionType mappingType);

    // Getters.
    // Get the list of languages of available mappings.
    tmzCollection<std::string> getLangList();
    // Get the list of encoding names of available mappings.
    tmzCollection<std::string> getEncodingList();
    // Get the mapping by encode name and mapping type.
    const tmzSP<tcMapping>& getMapping(const std::string& encodeName, tcConversionType mappingType);

private:
    // Internal implementation of register mapping.
    void registerMappingInternal(const tmzSP<tcMapping>& mapping);
    // Internal implementation of unregister mapping.
    void unregisterMappingInternal(const tmzSP<tcMapping>& mapping);

private:
    // Map of language code, encode and mapping ,mMap[lang][encode][0/1].
    tmzMap<std::string, tmzMap<std::string, tmzArray<tmzSP<tcMapping>, 2>>> mLangMap;
    // Map of encode name and mapping.
    tmzMap<std::string, tmzArray<tmzSP<tcMapping>, 2>> mEncodeMap;
};

} // namespace tmz
