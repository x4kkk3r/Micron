#ifndef _MICRON_ENGINE_RENDERER_VULKAN_PLATFORM_VULKAN_WINDOWS_SURFACE_H
#define _MICRON_ENGINE_RENDERER_VULKAN_PLATFORM_VULKAN_WINDOWS_SURFACE_H

#include "../VulkanSurface.h"

#if defined MICRON_CURRENT_PLATFORM_WINDOWS

#include <vulkan/vulkan_win32.h>

#define PLATFORM_SURFACE_EXTENSION_NAME VK_KHR_WIN32_SURFACE_EXTENSION_NAME

namespace Micron
{
    namespace Vulkan
    {
        class WindowsSurface : public Surface
        {
        public:
            inline WindowsSurface() noexcept = default;
            inline ~WindowsSurface() noexcept override = default;

            constexpr WindowsSurface(VkInstance instanceHandle, HWND windowHandle, HINSTANCE moduleHandle) noexcept :
                Surface(instanceHandle), windowHandle(windowHandle), moduleHandle(moduleHandle)
            {}

            Void CreateHandle() noexcept override;
        private:
            HWND windowHandle;
            HINSTANCE moduleHandle;
        };
    }
}

#else

namespace Micron
{
    namespace Vulkan
    {
        class WindowsSurface : public Surface
        {
        public:
            inline WindowsSurface() noexcept = default;
            inline ~WindowsSurface() noexcept override = default;

            Void CreateHandle() noexcept override { return; }
        };
    }
}

#endif

#endif