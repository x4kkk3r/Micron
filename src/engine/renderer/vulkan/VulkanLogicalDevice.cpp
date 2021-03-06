#include "VulkanLogicalDevice.h"

namespace Micron
{
    namespace Vulkan
    {
        Void LogicalDevice::CreateHandle(Vector<NullTerminatedConstantString> const &enabledExtensionNames) noexcept
        {
            VkDeviceCreateInfo deviceCreateInfo = {};
            deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

            auto queueCreateInfos = this->PickQueueCreateInfos();
            deviceCreateInfo.queueCreateInfoCount = static_cast<UInt32>(queueCreateInfos.size());
            deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();

            deviceCreateInfo.enabledExtensionCount = static_cast<UInt32>(enabledExtensionNames.size());
            deviceCreateInfo.ppEnabledExtensionNames = enabledExtensionNames.data();

            VkPhysicalDeviceFeatures enabledFeatures;
            vkGetPhysicalDeviceFeatures(this->physicalDeviceHandle, &enabledFeatures);
            deviceCreateInfo.pEnabledFeatures = &enabledFeatures;

            Utility::Result deviceCreate = vkCreateDevice(this->physicalDeviceHandle, &deviceCreateInfo, nullptr, &this->handle);

            if (deviceCreate.Failed())
            {
                CoreLogger::Error("Failed to create Vulkan logical device handle, message: {}", deviceCreate.ToString());
                return;
            }

            CoreLogger::Info("Vulkan logical device handle created");
        }
        
        Vector<VkDeviceQueueCreateInfo> LogicalDevice::PickQueueCreateInfos() const noexcept
        {
            Vector<VkDeviceQueueCreateInfo> queueCreateInfos;
            queueCreateInfos.reserve(queueFamilyIndices.size());

            std::ranges::for_each(std::as_const(queueFamilyIndices), [&](auto queueFamilyIndex)
            {
                VkDeviceQueueCreateInfo queueCreateInfo = {};
                queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
                queueCreateInfo.queueCount = LogicalDevice::queueCount;
                queueCreateInfo.pQueuePriorities = &LogicalDevice::queuePriority;

                queueCreateInfos.emplace_back(std::move(queueCreateInfo));
            });

            return queueCreateInfos;
        }

                
        Void LogicalDevice::InitializeQueues() noexcept
        {
            queues.reserve(queueFamilyIndices.size());

            std::ranges::for_each(std::as_const(queueFamilyIndices), [&](auto queueFamilyIndex)
            {
                VkQueue queueHandle;
                vkGetDeviceQueue(this->handle, queueFamilyIndex, LogicalDevice::queueIndex, &queueHandle);

                queues.emplace(queueFamilyIndex, new Queue(queueHandle));
            });
        }

        Void LogicalDevice::DestroyHandle() noexcept
        {
            if (this->handle == nullptr)
            {
                CoreLogger::Error("Can not destroy Vulkan logical device handle, because it is not created");
                return;
            }
            
            vkDestroyDevice(this->handle, nullptr);
        }
    }
}