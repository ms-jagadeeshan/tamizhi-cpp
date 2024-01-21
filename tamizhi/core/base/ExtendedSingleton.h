#pragma once
#include "tamizhi/core/base/Macros.h"

/************************************************************************************/

template <typename DerivedT>
class crExtendedSingleton
{
    TMZ_NON_COPYABLE(crExtendedSingleton);

public:
    static DerivedT* getInstance()
    {
        auto& instRef = getRawInstancePointer();
        return instRef;
    }

    static bool IsInitialized()
    {
        return getRawInstancePointer() != nullptr;
    }

protected:
    // Constructors.
    crExtendedSingleton() = default;
    virtual ~crExtendedSingleton() = default;

    template <typename... Args>
    static void startup(Args&&... args);
    static void startupWithInstance(DerivedT* instance);
    static void shutdown();
    static bool IsInitializedVar()
    {
        return mIsInit;
    };

    static DerivedT*& getRawInstancePointer()
    {
        static DerivedT* singletonInstance = nullptr;
        return singletonInstance;
    }

    inline static bool mIsInit = false;
};

/************************************************************************************/

template <typename DerivedT>
template <typename... Args>
void crExtendedSingleton<DerivedT>::startup(Args&&... args)
{
    checkAndReturn(!getInstance(), "Already initialized");
    startupWithInstance(new DerivedT(std::forward<Args>(args)...));
}

/************************************************************************************/

template <typename DerivedT>
void crExtendedSingleton<DerivedT>::startupWithInstance(DerivedT* instance)
{
    auto& instRef = getRawInstancePointer();
    if (instRef != nullptr)
    {
        tmzError("Already initialized");
        return;
    }
    instRef = instance;
}

/************************************************************************************/

template <typename DerivedT>
void crExtendedSingleton<DerivedT>::shutdown()
{
    auto& instRef = getRawInstancePointer();
    if (!instRef)
    {
        tmzError("Shutdown called without initialization");
        return;
    }
    delete instRef;
    instRef = nullptr;
}

/************************************************************************************/

#define TMZ_EXTENDED_SINGLETON(DerivedT) \
private:                                 \
    friend class crExtendedSingleton<DerivedT>;

/************************************************************************************/
