#pragma once

#include "tamizhi/core/base/Core.h"
#include "tamizhi/textConverter/mappingLoader/LoaderBase.h"

namespace tmz
{
class tcCSVLoader : public tcLoaderBase
{
    using BaseType = tcLoaderBase;

public:
    // Constructor.
    tcCSVLoader() = default;
    explicit tcCSVLoader(const crFilePath& file);
    ~tcCSVLoader() override = default;

private:
    // Implementation of reading the mapping.
    tmzSPCollection<tmz::tcMapping> readMappingInternal() override;
    // Implementation of write the mapping.
    bool writeMappingInternal(const tmzSPCollection<tmz::tcMapping>& mapping, const crFilePath& file) override;

private:
};

} // namespace tmz
