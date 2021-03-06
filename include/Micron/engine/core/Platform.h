#ifndef _MICRON_PLATFORM_H
#define _MICRON_PLATFORM_H

#include "types/BasicTypes.h"
#include "types/ContainerTypes.h"

#define MICRON_PLATFORM_WINDOWS 0
#define MICRON_PLATFORM_LINUX 1
#define MICRON_PLATFORM_MACOS 2

namespace Micron
{
    enum class Platform : UInt16
    {
        Windows = MICRON_PLATFORM_WINDOWS,
        Linux = MICRON_PLATFORM_LINUX,
        MacOS = MICRON_PLATFORM_MACOS
    };

    MultibyteString ToString(Platform const &platform) noexcept;
}

#if defined(__linux__) && !defined(__ANDROID__)
    #define MICRON_CURRENT_PLATFORM ::Micron::Platform::Linux
#elif defined(_WIN32) || defined(_WIN64)
    #define MICRON_CURRENT_PLATFORM ::Micron::Platform::Windows
#elif defined(__APPLE__)
    #define MICRON_CURRENT_PLATFORM ::Micron::Platform::MacOS
#else
    static_assert(false, "Unknown platform")
#endif

#endif