#include "tamizhi/textConverter/mapping/Mapping.h"

/********************************************************************/

tmz::tcMapping::tcMapping(const std::string& encodeName, const std::string& langCode, tcConversionType mappingType)
    : mLangCode(langCode), mEncodeName(encodeName), mMappingType(mappingType)
{
}

/********************************************************************/

void tmz::tcMapping::langCode(const std::string& langCode)
{
    mLangCode = langCode;
}

/********************************************************************/

void tmz::tcMapping::encodeName(const std::string& encodeName)
{
    mEncodeName = encodeName;
}

/********************************************************************/

void tmz::tcMapping::mappingType(tcConversionType mappingType)
{
    mMappingType = mappingType;
}

/********************************************************************/

void tmz::tcMapping::setEncodeToUnicode(bool isEncodeToUnicode)
{
    if (isEncodeToUnicode)
    {
        mMappingType = ENCODE_TO_UNICODE;
    }
    else
    {
        mMappingType = UNICODE_TO_ENCODE;
    }
}

/********************************************************************/

void tmz::tcMapping::maxMatchLength(int maxMatchLength)
{
    mMaxMatchLength = maxMatchLength;
}

/********************************************************************/

void tmz::tcMapping::gcdCharSize(int gcdCharSize)
{
    mGcdCharSize = gcdCharSize;
}

/********************************************************************/

bool tmz::tcMapping::insert(std::string key, std::string value)
{
    mMapping->emplace(key, value);
    return true;
}

/********************************************************************/

bool tmz::tcMapping::insert(const tmzCollection<std::string>& keys, const tmzCollection<std::string>& values)
{
    checkAndReturnValue(keys.size() == values.size(), "[Encode Unicode Converter] Keys and values vector size does not match", false);

    for (std::size_t i = 0; i < keys.size(); i++)
    {
        mMapping->emplace(keys[i], values[i]);
    }
    return true;
}

/********************************************************************/

std::string tmz::tcMapping::convert(const std::string& input)
{
    std::string result;

    for (auto it = input.begin(); it != input.end();)
    {
        const auto& old_it = it;

        for (auto len = std::min(std::distance(it, input.end()), static_cast<std::ptrdiff_t>(mMaxMatchLength));
             len > 0; len = len - mGcdCharSize)
        {
            auto substr = std::string(it, it + len);
            auto mappingItr = mMapping->find(substr);

            if (mappingItr != mMapping->end())
            {
                result += mappingItr->second;
                std::advance(it, len);
                break;
            }
        }

        // If not found in mapping, just increment iterator.
        if (old_it == it)
        {
            result += *it++;
        }
    }
    return result;
}

/********************************************************************/

std::string tmz::tcMapping::langCode()
{
    return mLangCode;
}

/********************************************************************/

std::string tmz::tcMapping::encodeName()
{
    return mEncodeName;
}

/********************************************************************/

const tmzSP<tmzEUMap>& tmz::tcMapping::mapping()
{
    return mMapping;
}

/********************************************************************/

bool tmz::tcMapping::isEncodeToUnicode()
{
    return (mMappingType == ENCODE_TO_UNICODE);
}

/********************************************************************/

tcConversionType tmz::tcMapping::mappingType()
{
    return mMappingType;
}

/********************************************************************/

std::size_t tmz::tcMapping::maxMatchLength()
{
    return mMaxMatchLength;
}
/********************************************************************/

std::size_t tmz::tcMapping::gcdCharSize()
{
    return mGcdCharSize;
}

/********************************************************************/

void tmz::tcMapping::print()
{
    tmzPrint("+-------------------------------------------+\n");
    tmzPrint("Language Code: %s\n", mLangCode.c_str());
    tmzPrint("Encode Name  : %s\n", mEncodeName.c_str());
    tmzPrint("Mapping type : %s\n", mMappingType == ENCODE_TO_UNICODE ? "Encode to Unicode" : "Unicode to encode");
    tmzPrint("Max Matching Length  : %zu\n", mMaxMatchLength);
    tmzPrint("GCD of Character Size: %zu\n", mGcdCharSize);
    tmzPrint("Mappings>\n");
    for (const auto& [key, value] : *mMapping)
    {
        tmzPrint("%s --> %s\n", key.c_str(), value.c_str());
    }
    tmzPrint("+-------------------------------------------+\n");
}

/********************************************************************/

void tmz::tcMapping::replaceAll(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        tmzPrint("hello");
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', advance start_pos to avoid infinite loop
    }
}

/********************************************************************/
