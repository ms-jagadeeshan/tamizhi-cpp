#pragma once

#include "tamizhi/core/base/Core.h"
#include "tamizhi/textConverter/mappingLoader/LoaderBase.h"

namespace tmz
{
class tcJSONLoader : public tcLoaderBase
{
    using BaseType = tcLoaderBase;

public:
    // Constructor.
    tcJSONLoader() = default;
    explicit tcJSONLoader(const crFilePath& file);
    ~tcJSONLoader() override = default;

private:
    // Implementation of reading the mapping.
    tmzSPCollection<tmz::tcMapping> readMappingInternal() override;
    // Implementation of write the mapping.
    bool writeMappingInternal(const tmzSPCollection<tmz::tcMapping>& mapping, const crFilePath& file) override;

private:
};

} // namespace tmz
