#include "tamizhi/core/base/Core.h"
#include "tamizhi/core/file/FileUtils.h"
#include "tamizhi/textConverter/mapping/Mapping.h"
#include "tamizhi/textConverter/mappingLoader/MappingLoader.h"

int main(void)
{
    // Can give json, xml, csv
    auto mappings = tmz::tcMappingLoader::read(crFilePath("data://mappings/ta_mappings.xml"));
    // Printing the mappping.
    for (const auto& mapping : mappings)
    {
        // mapping->print();
    }

    std::string data1 = "世界有";
    tmzPrint("data1 size : %zu\n", data1.size());
    data1 = "மி";
    tmzPrint("data1 size : %zu\n", data1.size());
    auto timer = crTimeProfiler();
    std::string data = "தமிழ்";

    ProfilerStart("cpuprofile.txt");
    std::string unicodeData;
    tmz::loadFromFile(unicodeData, crFilePath("data://corpus/Wikipedia_Ariviyal.txt"));

    timer.start();
    auto result = mappings[1]->convert(unicodeData);
    timer.printTimeElapsed();

    // tmz::saveToFile(result, crFilePath("data://tests/unicodeToEncode.txt"));

    std::string encodeData;
    // tmz::loadFromFile(encodeData, crFilePath("data://tests/unicodeToEncode.txt"));

    timer.start();
    result = mappings[0]->convert(result);
    timer.printTimeElapsed();
    ProfilerStop();
    tmz::saveToFile(result, crFilePath("data://tests/encodeToUnicode.txt"));
}
