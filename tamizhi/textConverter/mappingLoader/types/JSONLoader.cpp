#include "tamizhi/textConverter/mappingLoader/types/JSONLoader.h"

/********************************************************************/

tmz::tcJSONLoader::tcJSONLoader(const crFilePath& file)
    : BaseType(file)
{
}

/********************************************************************/

tmzSPCollection<tmz::tcMapping> tmz::tcJSONLoader::readMappingInternal()
{
    tmzSP<tmz::tcMapping> mapping = std::make_shared<tmz::tcMapping>();

    return {};
}

/********************************************************************/

bool tmz::tcJSONLoader::writeMappingInternal(const tmzSPCollection<tmz::tcMapping>& mapping, const crFilePath& file)
{
    return false;
}

/********************************************************************/
