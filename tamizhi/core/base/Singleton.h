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
        std::call_once(onceFlag, []() {
            instance = new DerivedT();
        });
        return instance;
    }

    // Delete copy constructor and copy assignment operator
    crSingleton(const crSingleton&) = delete;
    crSingleton& operator=(const crSingleton&) = delete;
    crSingleton(const DerivedT&) = delete;
    DerivedT& operator=(const DerivedT&) = delete;

protected:
    crSingleton() = default;
    ~crSingleton() = default;

private:
    static DerivedT* instance;
    static std::once_flag onceFlag;
};

/********************************************************************/

#define TMZ_AUTO_SINGLETON(DerivedT) \
private:                             \
    friend class crSingleton<DerivedT>;

/********************************************************************/
