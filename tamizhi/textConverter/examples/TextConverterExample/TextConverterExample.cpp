#include "tamizhi/textConverter/converter/Converter.h"

using tmz::TextConverter;
int main()
{
    TextConverter tc;
    tc.loadFromFile(crFilePath("data://mappings/ta_mappings.xml"));
    tc.setEncoding("tace16", tcConversionType::UNICODE_TO_ENCODE);

    tmzSleep(100000000);
}
