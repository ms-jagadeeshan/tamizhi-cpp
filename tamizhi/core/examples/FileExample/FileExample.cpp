#include "tamizhi/core/base/Profiler.h"
#include "tamizhi/core/file/FilePath.h"

int main()
{
    ProfilerStart("helo.txt");
    auto Profiler = crTimeProfiler();
    crFilePath filePath("log://FileExample.cpp");

    tmzPrint("%s\n", filePath.get().c_str());
    tmzPrint("%s\n", filePath.getFileName().c_str());
    tmzPrint("%s\n", filePath.getExtension().c_str());

    crFilePath filePath1("/FileExample.cpp");

    tmzPrint("%s\n", filePath1.get().c_str());
    tmzPrint("%s\n", filePath1.getFileName().c_str());
    tmzPrint("%s\n", filePath1.getExtension().c_str());

    crFilePath filePath2("~/FileExample.cpp");

    tmzPrint("%s\n", filePath2.get().c_str());
    tmzPrint("%s\n", filePath2.getFileName().c_str());
    tmzPrint("%s\n", filePath2.getExtension().c_str());
    Profiler.printTimeElapsed();
    ProfilerStop();
}
