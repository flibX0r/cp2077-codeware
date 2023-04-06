#pragma once

namespace Core
{
class RawBase
{
public:
    constexpr RawBase() = default;

    inline static uintptr_t GetImageBase()
    {
        static const auto base = reinterpret_cast<uintptr_t>(GetModuleHandleW(nullptr));
        return base;
    }
};

template<uintptr_t A, typename T>
class RawFunc {};

template<uintptr_t A, typename R, typename... Args>
class RawFunc<A, R (*)(Args...)> : public RawBase
{
public:
    using Type = R (*)(Args...);
    using Callable = Type;

    static constexpr uintptr_t offset = A;

    constexpr RawFunc() = default;

    operator bool() const noexcept
    {
        return GetPtr() != nullptr;
    }

    [[nodiscard]] inline operator Callable() const
    {
        return GetPtr();
    }

    [[nodiscard]] inline Callable GetPtr() const noexcept
    {
        return reinterpret_cast<Callable>(GetAddress());
    }

    inline static uintptr_t GetAddress() noexcept
    {
        if (!address)
        {
            ResetAddress();
        }

        return address;
    }

    inline static void ResetAddress() noexcept
    {
        address = offset ? offset + GetImageBase() : 0;
    }

    inline static void SetAddress(uintptr_t aAddress) noexcept
    {
        address = aAddress;
    }

    inline static R Invoke(Args... aArgs)
    {
        return reinterpret_cast<Callable>(GetAddress())(std::forward<Args>(aArgs)...);
    }

private:
    inline static uintptr_t address = 0;
};

template<uintptr_t A, typename C, typename R, typename... Args>
class RawFunc<A, R (C::*)(Args...)> : public RawFunc<A, R (*)(C*, Args...)>
{
public:
    using Base = RawFunc<A, R (*)(C*, Args...)>;
    using Base::Base;
};

template<uintptr_t A, typename T>
class RawPtr : public RawBase
{
public:
    using Type = std::conditional_t<std::is_pointer_v<T>, std::remove_pointer_t<T>, T>;
    using Ptr = Type*;

    static constexpr uintptr_t offset = A;
    static constexpr bool indirect = std::is_pointer_v<T>;

    constexpr RawPtr() = default;

    operator bool() const noexcept
    {
        return GetPtr() != nullptr;
    }

    [[nodiscard]] inline operator Type&() const
    {
        if constexpr (indirect)
        {
            return **GetPtr();
        }
        else
        {
            return *GetPtr();
        }
    }

    [[nodiscard]] inline operator Type*() const
    {
        if constexpr (indirect)
        {
            return *GetPtr();
        }
        else
        {
            return GetPtr();
        }
    }

    [[nodiscard]] inline Type* operator->() const
    {
        if constexpr (indirect)
        {
            return *GetPtr();
        }
        else
        {
            return GetPtr();
        }
    }

    RawPtr& operator=(T&& aRhs) const noexcept
    {
        *GetPtr() = aRhs;
        return *this;
    }

    [[nodiscard]] inline T* GetPtr() const noexcept
    {
        return reinterpret_cast<T*>(GetAddress());
    }

    inline static uintptr_t GetAddress() noexcept
    {
        static uintptr_t addr = offset ? offset + GetImageBase() : 0;
        return addr;
    }

    inline static T* Get()
    {
        return reinterpret_cast<T*>(GetAddress());
    }
};

template<typename T>
inline T* OffsetPtr(void* aBase, uintptr_t aOffset)
{
    return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(aBase) + aOffset);
}
}
