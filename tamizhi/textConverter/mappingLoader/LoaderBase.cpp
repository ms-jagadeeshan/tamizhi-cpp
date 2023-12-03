#include "tamizhi/textConverter/mappingLoader/LoaderBase.h"

/********************************************************************/

tmz::tcLoaderBase::tcLoaderBase(const crFilePath& path)
    : mFilePath(path)
{
}

/********************************************************************/

// tmz::euLoaderBase::euLoaderBase(const std::string& data)
//     : mFilePath(""), mData(data)
// {
// }

/********************************************************************/

void tmz::tcLoaderBase::setData(const std::string& data)
{
    mData = data;
    mFilePath = crFilePath("");
}

/********************************************************************/

tmzSPCollection<tmz::tcMapping> tmz::tcLoaderBase::readMapping(const crFilePath& file)
{
    mFilePath = file;
    mData = "";
    return readMappingInternal();
}

/********************************************************************/

tmzSPCollection<tmz::tcMapping> tmz::tcLoaderBase::readMapping()
{
    return readMappingInternal();
}

/********************************************************************/

bool tmz::tcLoaderBase::writeMapping(const tmzSPCollection<tmz::tcMapping>& mapping, const crFilePath& file)
{
    return writeMappingInternal(mapping, file);
}

/********************************************************************/
