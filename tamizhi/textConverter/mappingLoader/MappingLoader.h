#pragma once

#include "tamizhi/core/base/Core.h"

namespace tmz
{

class tcMapping;
class tcLoaderBase;
class tcMappingLoader
{
public:
    // Read the mapping from file.
    static tmzSPCollection<tmz::tcMapping> read(const crFilePath& file);
    // Read the mapping from string data.
    static tmzSPCollection<tmz::tcMapping> readFromString(const std::string& data, const std::string dataFileType);
    // Write the mapping to a file.
    static bool write(const tmzSPCollection<tmz::tcMapping>& mappings, const crFilePath& file);

protected:
    static tmzSP<tmz::tcLoaderBase> getLoader(const std::string& dataFileType);
};

} // namespace tmz
