#pragma once
#include <memory>
#include <mutex>

/********************************************************************/

template <typename DerivedT>
class crSingleton
{
public:
    static DerivedT*& getInstance()
    {
        static DerivedT* mInstance = nullptr;
        static std::once_flag onceFlag;
        std::call_once(onceFlag, []() {
            mInstance = new DerivedT();
        });
        return mInstance;
    }

    // Delete copy constructor and copy assignment operator
    crSingleton(const crSingleton&) = delete;
    crSingleton& operator=(const crSingleton&) = delete;
    crSingleton(const DerivedT&) = delete;
    DerivedT& operator=(const DerivedT&) = delete;

protected:
    crSingleton() = default;
    virtual ~crSingleton() = default;
};

/********************************************************************/

#define TMZ_AUTO_SINGLETON(DerivedT) \
private:                             \
    friend class crSingleton<DerivedT>;

/********************************************************************/
