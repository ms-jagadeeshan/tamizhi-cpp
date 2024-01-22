#include "tamizhi/textConverter/mappingLoader/MappingLoader.h"
#include "tamizhi/textConverter/mapping/Mapping.h"
#include "tamizhi/textConverter/mappingLoader/types/CSVLoader.h"
#include "tamizhi/textConverter/mappingLoader/types/JSONLoader.h"
#include "tamizhi/textConverter/mappingLoader/types/XMLLoader.h"

/********************************************************************/

tmzCollection<tmzSP<tmz::tcMapping>> tmz::tcMappingLoader::read(const crFilePath& file)
{
    std::string msg = "[Mapping Loader] Failed to read mapping from file: " + file.get();
    checkAndReturnValue(file.isValid(), msg.c_str(), {});
    checkAndReturnValue(file.isFile(), msg.c_str(), {});

    // Get the loader.
    tmzSP<tmz::tcLoaderBase> loader = tmz::tcMappingLoader::getLoader(file.getExtension());
    checkAndReturnValue(loader != nullptr, "", {});
    // Read the mappings.
    auto mapping = loader->readMapping(file);

    return mapping;
}

/********************************************************************/

tmzCollection<tmzSP<tmz::tcMapping>> tmz::tcMappingLoader::readFromString(const std::string& data, const std::string dataFileType)
{
    checkAndReturnValue(!crUtils::empty(data), "[Mapping Loader] Data is empty", {});

    tmzSP<tmz::tcLoaderBase> loader = tmz::tcMappingLoader::getLoader(dataFileType);
    checkAndReturnValue(loader != nullptr, "", {});

    loader->setData(data);
    auto mapping = loader->readMapping();

    return mapping;
}

/********************************************************************/

bool tmz::tcMappingLoader::write(const tmzSPCollection<tmz::tcMapping>& mappings, const crFilePath& file)
{
    checkAndReturnValue(!mappings.empty(), "[Mapping Loader] Mapping is empty", false);

    // Get the loader.
    tmzSP<tmz::tcLoaderBase> loader = tmz::tcMappingLoader::getLoader(file.getExtension());
    checkAndReturnValue(loader != nullptr, "", false);

    return loader->writeMapping(mappings, file);
}

/********************************************************************/

tmzSP<tmz::tcLoaderBase> tmz::tcMappingLoader::getLoader(const std::string& dataFileType)
{
    checkAndReturnValue(!crUtils::empty(dataFileType), "[Mapping Loader] Data file type is empty", nullptr);

    tmzSP<tmz::tcLoaderBase> loader;
    if (crUtils::iequals(dataFileType, "xml"))
    {
        loader = std::make_shared<tmz::tcXMLLoader>();
    }
    else if (crUtils::iequals(dataFileType, "csv"))
    {
        loader = std::make_shared<tmz::tcCSVLoader>();
    }
    else if (crUtils::iequals(dataFileType, "json"))
    {
        loader = std::make_shared<tmz::tcJSONLoader>();
    }

    if (loader == nullptr)
        tmzError("[Mapping Loader] Unsupported file type: %s", dataFileType.c_str());

    return loader;
}

/********************************************************************/
