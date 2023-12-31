#include "tamizhi/core/base/Core.h"

int main()
{
    crFilePath file("data://corpus/Wikipedia_Ariviyal.txt");

    auto timer = crTimeProfiler("UTF");

    std::string data;
    tmz::loadFromFile(data, file);

    auto dataSize = data.size();
    size_t totalBytesRead = 0;
    size_t bytesRead = 0;
    // tmzCollection<uint_least32_t> codePoints;
    // codePoints.reserve(dataSize);

    ProfilerStart("myprofile.txt");
    timer.start();

    auto cps = crUtils::decodeUtf8(data.cbegin(), data.cend(), bytesRead);

    timer.printTimeElapsed("Decode Time");

    timer.start();
    std::string encode_data;
    for (auto& cp : *cps)
    {
        encode_data += crUtils::encodeUtf8(cp);
    }
    timer.printTimeElapsed("Encode Time");

    tmz::saveToFile(encode_data, crFilePath("data://tests/Wikipedia_Ariviyal.txt"));

    timer.start();

    std::string encode_data_1;
    encode_data_1 = crUtils::encodeUtf8(*cps);

    timer.printTimeElapsed("Encode Time 1");

    tmz::saveToFile(encode_data, crFilePath("data://tests/Wikipedia_Ariviyal1.txt"));
    ProfilerStop();
}
// while (totalBytesRead < dataSize)
// {
//     auto cp = crUtils::decodeUtf8(data, bytesRead);
//     if (cp != 0)
//     {
//         codePoints.emplace_back(cp);
//     }
// }
