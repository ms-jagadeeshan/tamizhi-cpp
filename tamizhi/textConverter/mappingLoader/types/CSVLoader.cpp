#include "tamizhi/textConverter/mappingLoader/types/CSVLoader.h"

/********************************************************************/

tmz::tcCSVLoader::tcCSVLoader(const crFilePath& file)
    : BaseType(file)
{
}

/********************************************************************/

tmzSPCollection<tmz::tcMapping> tmz::tcCSVLoader::readMappingInternal()
{
    tmzSP<tmz::tcMapping> mapping = std::make_shared<tmz::tcMapping>();

    return {mapping};
}

/********************************************************************/

bool tmz::tcCSVLoader::writeMappingInternal(const tmzSPCollection<tmz::tcMapping>& mapping, const crFilePath& file)
{
    return false;
}

/*******************************************************************/
