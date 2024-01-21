#pragma once

#include <memory>

namespace tmz
{
template <typename T>
class crRawPointer
{
public:
    // Constructors.
    crRawPointer()
        : mPtr(nullptr)
    {
    }

    crRawPointer(const crRawPointer& ptr)
        : mPtr(const_cast<T*>(ptr.get()))
    {
    }
    explicit crRawPointer(const std::shared_ptr<T>& ptr)
        : mPtr(ptr.get())
    {
    }

    explicit crRawPointer(const std::unique_ptr<T>& ptr)
        : mPtr(ptr.get())
    {
    }

    explicit crRawPointer(const T* ptr)
        : mPtr(const_cast<T*>(ptr))
    {
    }
    T* get()
    {
        return mPtr;
    };

    const T* get() const
    {
        return mPtr;
    };

    void reset()
    {
        mPtr = nullptr;
    };

    /// Access the object referenced by this reference
    T* operator->()
    {
        return mPtr;
    };

    T* const operator->() const
    {
        return mPtr;
    };

    // Compare this reference with another reference
    bool operator==(const T* pointer) const
    {
        if (mPtr == pointer)
            return true;
        else
            return false;
    }

    // Compare this reference with another reference
    bool operator==(const crRawPointer<T> pointer) const
    {
        if (mPtr == pointer.mPtr)
            return true;
        else
            return false;
    }

    // Compare this reference with nullptr
    bool operator==(std::nullptr_t) const
    {
        return (*this == crRawPointer<T>());
    }

    // Inequality check of this reference with pointer
    bool operator!=(T* pointer) const
    {
        return !operator==(pointer);
    }

    // Inequality check of this reference with pointer
    bool operator!=(const T* pointer) const
    {
        return !operator==(pointer);
    }

    // Inequality check of this reference with reference
    bool operator!=(const crRawPointer<T> pointer) const
    {
        return !operator==(pointer);
    }

    // Inequality check of this reference with nullptr
    bool operator!=(std::nullptr_t) const
    {
        return (*this != crRawPointer<T>());
    }
    // Inequality check of this reference with nullptr
    bool operator!() const
    {
        return (mPtr == nullptr);
    }

    // Return a C++ reference to the referenced object
    T& operator*()
    {
        return *mPtr;
    }

    /// Return a const C++ reference to the referenced object
    const T& operator*() const
    {
        return *mPtr;
    };

    crRawPointer& operator=(std::nullptr_t)
    {
        mPtr = nullptr;
        return *this;
    }

    // Copy from pointer.
    crRawPointer& operator=(T* pointer)
    {
        mPtr = pointer;
        return *this;
    }

    // Copy from shared pointer.
    crRawPointer& operator=(std::shared_ptr<T> ptr)
    {
        mPtr = ptr.get();
        return *this;
    }

    // Copy from unique pointer.
    crRawPointer& operator=(std::unique_ptr<T> ptr)
    {
        mPtr = ptr.get();
        return *this;
    }

private:
    // Store the pointer.
    T* mPtr = nullptr;
};
} // namespace tmz
