#include <memory>
#include <mutex>

template <typename DerivedT>
class crSingleton
{
public:
    static DerivedT& getInstance()
    {
        std::call_once(onceFlag, []() {
            instance.reset(new DerivedT());
        });
        return *instance;
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
    static std::unique_ptr<DerivedT> instance;
    static std::once_flag onceFlag;
};
