#include "tamizhi/core/base/UTF8Utils.h"

/********************************************************************/

std::string crUtils::encodeUtf8(const std::vector<uint_least32_t>& codePoints)
{
    std::string utf8String;
    utf8String.reserve(codePoints.size() * 4); // Reserve space for efficiency

    for (const auto& cp : codePoints)
    {
        int bytesNeededForCodePoint = bytesNeeded(cp);
        assert(bytesNeededForCodePoint > 0 && bytesNeededForCodePoint <= 4); // Assertion for development

        unsigned char utf8Buffer[4];
        unsigned char* utf8Ptr = utf8Buffer + bytesNeededForCodePoint - 1;

        switch (bytesNeededForCodePoint)
        {
        case 4:
            *utf8Ptr-- = 0x80 | (cp & 0x3F);
            *utf8Ptr-- = 0x80 | ((cp >> 6) & 0x3F);
            *utf8Ptr-- = 0x80 | ((cp >> 12) & 0x3F);
            *utf8Ptr-- = 0xF0 | ((cp >> 18) & 0x07);
            break;
        case 3:
            *utf8Ptr-- = 0x80 | (cp & 0x3F);
            *utf8Ptr-- = 0x80 | ((cp >> 6) & 0x3F);
            *utf8Ptr-- = 0xE0 | ((cp >> 12) & 0x0F);
            break;
        case 2:
            *utf8Ptr-- = 0x80 | (cp & 0x3F);
            *utf8Ptr-- = 0xC0 | ((cp >> 6) & 0x1F);
            break;
        case 1:
            *utf8Ptr = static_cast<unsigned char>(cp);
            break;
        default: // Handle invalid case
            assert(false); // Assertion for development
            continue; // Skip invalid code points
        }

        utf8String.append(reinterpret_cast<char*>(utf8Buffer), bytesNeededForCodePoint);
    }

    return utf8String;
}

/********************************************************************/

std::shared_ptr<std::vector<uint_least32_t>> crUtils::decodeUtf8(std::string::const_iterator itBegin, std::string::const_iterator itEnd, size_t& bytesRead)
{
    std::shared_ptr<std::vector<uint_least32_t>> codePoints = std::make_shared<std::vector<uint_least32_t>>();
    codePoints->reserve(std::distance(itBegin, itEnd) >> 2);

    std::size_t extraBytes = 0;
    uint_least32_t codePoint = 0;
    while (itBegin != itEnd)
    {
        extraBytes = 0;
        codePoint = 0;

        if ((*itBegin & 0x80) == 0)
        {
            // Single-byte character
            codePoint = *itBegin;
            bytesRead += 1;
        }
        else if ((*itBegin & 0xE0) == 0xC0)
        {
            // Two-byte character
            codePoint = *itBegin & 0x1F;
            extraBytes = 1;
        }
        else if ((*itBegin & 0xF0) == 0xE0)
        {
            // Three-byte character
            codePoint = *itBegin & 0x0F;
            extraBytes = 2;
        }
        else if ((*itBegin & 0xF8) == 0xF0)
        {
            // Four-byte character
            codePoint = *itBegin & 0x07;
            extraBytes = 3;
        }
        else
        {
            tmzError("Warning: Invalid UTF-8 sequence encountered.");
        }

        ++itBegin;
        bytesRead += extraBytes;
        for (std::size_t i = 0; i < extraBytes; ++i)
        {

            codePoint = (codePoint << 6) | (*itBegin & 0x3F);
            ++itBegin;
        }

        codePoints->emplace_back(codePoint);
    }
    return codePoints;
}

/********************************************************************/
