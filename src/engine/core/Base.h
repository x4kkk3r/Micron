#ifndef _MICRON_CORE_BASE_H
#define _MICRON_CORE_BASE_H

#include <memory>
#include <cstddef>
#include <cassert>

#include <ranges>

#include "Platform.h"

#if defined _MICRON_DEBUG
    #define _MICRON_DEBUG_ENABLED 1

    #if MICRON_PLATFORM == MICRON_PLATFORM_WINDOWS
        #define _MICRON_DEBUG_BREAK() __debugbreak()
    #elif MICRON_PLATFORM == MICRON_PLATFORM_LINUX
        #include <signal.h>
        #define _MICRON_DEBUG_BREAK() raise(SIGTRAP)
    #else
       static_assert(false, "Abort for the current platform is not supported")
    #endif

    #define _MICRON_ASSERT(condition) if (!(condition)) _MICRON_DEBUG_BREAK()
#else
    #define _MICRON_DEBUG_ENABLED 0
    #define _MICRON_DEBUG_BREAK()
    #define _MICRON_ASSERT(condition)
#endif

#define _MICRON_SHUTDOWN() exit(-1)

namespace Micron
{
    constexpr Bool IsDebugEnabled() noexcept { return static_cast<Bool>(_MICRON_DEBUG_ENABLED); }

    template <typename T> using Box = std::unique_ptr<T>;
    template <typename T> using Rc = std::shared_ptr<T>;

    template <typename T, typename ...Args> constexpr Box<T> MakeBox(Args &&...args) noexcept
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename ...Args> constexpr Rc<T> MakeRc(Args &&...args) noexcept
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template <typename T, typename U> constexpr Rc<T> DynamicPointerCast(Rc<U> const &pointer) noexcept
    {
        return std::dynamic_pointer_cast<T, U>(pointer);
    }
}

#endif