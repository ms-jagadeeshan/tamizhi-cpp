#pragma once

#include "tamizhi/core/base/Core.h"
#include "tamizhi/textConverter/mapping/Mapping.h"

/********************************************************************/

namespace tmz
{
class tcMapping;

class tcLoaderBase
{
public:
    // Constructor.
    explicit tcLoaderBase(const crFilePath& path = crFilePath(""));
    // Destructor.
    virtual ~tcLoaderBase() = default;

    // Set the data.
    void setData(const std::string& data);

    // Read the mapping from file.
    tmzSPCollection<tmz::tcMapping> readMapping(const crFilePath& file);
    // Read the mapping from string data.
    tmzSPCollection<tmz::tcMapping> readMapping();
    // Write the mapping to file.
    bool writeMapping(const tmzSPCollection<tmz::tcMapping>& mappings, const crFilePath& file);

protected:
    // Internal implementation of mapping reader.
    virtual tmzSPCollection<tmz::tcMapping> readMappingInternal() = 0;
    // Internal implementation of mapping writer.
    virtual bool writeMappingInternal(const tmzSPCollection<tmz::tcMapping>& mappings, const crFilePath& file) = 0;

protected:
    // Store the file path.
    crFilePath mFilePath;
    // Store the data.
    std::string mData = "";
};
} // namespace tmz

/********************************************************************/
