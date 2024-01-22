#pragma once

#include "tamizhi/core/base/PrintUtils.h"
#include "tamizhi/core/base/Utils.h"

/************************************************************************************/

#define checkAndReturnValue(condition, message, value) \
    if (!(condition))                                  \
    {                                                  \
        if (!crUtils::empty(message))                  \
        {                                              \
            tmzError("%s", message);                   \
        }                                              \
        return value;                                  \
    }                                                  \
    (void)(0)

/************************************************************************************/

#define checkAndReturn(condition, message) \
    if (!(condition))                      \
    {                                      \
        if (!crUtils::empty(message))      \
        {                                  \
            tmzError("%s", message);       \
        }                                  \
        return;                            \
    }                                      \
    (void)(0)

/************************************************************************************/

#define TMZ_NON_COPYABLE(Class)   \
    Class(const Class&) = delete; \
    Class& operator=(const Class&) = delete

/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
/************************************************************************************/
