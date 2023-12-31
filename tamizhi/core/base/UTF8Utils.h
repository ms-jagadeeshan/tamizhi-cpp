#pragma once

#include "tamizhi/core/base/Memory.h"
#include "tamizhi/core/base/PrintUtils.h"
#include <cassert>
#include <cstdint>
#include <string>

namespace crUtils
{
// Encode a collection of code points.
std::string encodeUtf8(const std::vector<uint_least32_t>& codePoints);

/********************************************************************/

// Decode the entire string.
std::shared_ptr<std::vector<uint_least32_t>> decodeUtf8(std::string::const_iterator itBegin, std::string::const_iterator itEnd, size_t& bytesRead);

/********************************************************************/

inline constexpr int bytesNeeded(uint_least32_t cp) noexcept
{
    if (cp <= 0x7F)
        return 1;
    else if (cp <= 0x7FF)
        return 2;
    else if (cp <= 0xFFFF)
        return 3;
    else if (cp <= 0x10FFFF)
        return 4;
    else
        return 0;
}

/********************************************************************/

inline int bytesNeeded(const std::string& str) noexcept
{
    if (str.empty())
        return 0;

    if ((str[0] & 0x80) == 0)
        return 1;
    else if ((str[0] & 0xE0) == 0xC0)
        return 2;
    else if ((str[0] & 0xF0) == 0xE0)
        return 3;
    else if ((str[0] & 0xF8) == 0xF0)
        return 4;
    else
        return 0;
}

/********************************************************************/

// Encode one code point.
inline std::string encodeUtf8(uint_least32_t cp)
{
    int bytesNeededForCodePoint = bytesNeeded(cp);
    if (bytesNeededForCodePoint == 0)
    {
        // Handle invalid code point
        return "";
    }

    std::string utf8String;
    utf8String.resize(bytesNeededForCodePoint);

    unsigned char* utf8Buffer = reinterpret_cast<unsigned char*>(&utf8String[0]);
    for (int i = 0; i < bytesNeededForCodePoint; ++i)
    {
        utf8Buffer[i] = 0;
    }

    utf8Buffer = utf8Buffer + bytesNeededForCodePoint - 1;

    switch (bytesNeededForCodePoint)
    {
    case 4:
        *utf8Buffer-- = 0x80 | (cp & 0x3F);
        *utf8Buffer-- = 0x80 | ((cp >> 6) & 0x3F);
        *utf8Buffer-- = 0x80 | ((cp >> 12) & 0x3F);
        *utf8Buffer-- = 0xF0 | ((cp >> 18) & 0x07);
        break;
    case 3:
        *utf8Buffer-- = 0x80 | (cp & 0x3F);
        *utf8Buffer-- = 0x80 | ((cp >> 6) & 0x3F);
        *utf8Buffer-- = 0xE0 | ((cp >> 12) & 0x0F);
        break;
    case 2:
        *utf8Buffer-- = 0x80 | (cp & 0x3F);
        *utf8Buffer-- = 0xC0 | ((cp >> 6) & 0x1F);
        break;
    case 1:
        *utf8Buffer = static_cast<unsigned char>(cp);
        break;
    default: // Handle invalid case
        return "";
    }

    return utf8String;
}

/********************************************************************/

// Decode one code point.
inline uint_least32_t decodeUtf8(const std::string& utf8, size_t& bytesRead) noexcept
{
    if (utf8.empty())
    {
        bytesRead = 0;
        return 0;
    }

    const unsigned char* utf8Buffer = reinterpret_cast<const unsigned char*>(utf8.c_str());
    std::size_t extraBytes = 0;
    uint_least32_t codePoint = 0;

    if ((utf8Buffer[0] & 0x80) == 0)
    {
        // Single-byte character
        codePoint = utf8Buffer[0];
        bytesRead = 1;
    }
    else if ((utf8Buffer[0] & 0xE0) == 0xC0)
    {
        // Two-byte character
        codePoint = utf8Buffer[0] & 0x1F;
        extraBytes = 1;
    }
    else if ((utf8Buffer[0] & 0xF0) == 0xE0)
    {
        // Three-byte character
        codePoint = utf8Buffer[0] & 0x0F;
        extraBytes = 2;
    }
    else if ((utf8Buffer[0] & 0xF8) == 0xF0)
    {
        // Four-byte character
        codePoint = utf8Buffer[0] & 0x07;
        extraBytes = 3;
    }

    for (std::size_t i = 0; i < extraBytes; ++i)
    {
        codePoint = (codePoint << 6) | (utf8Buffer[i + 1] & 0x3F);
    }

    bytesRead = extraBytes + 1;
    return codePoint;
}
} // namespace crUtils
