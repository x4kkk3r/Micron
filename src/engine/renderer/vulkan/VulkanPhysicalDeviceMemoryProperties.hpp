#ifndef _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_PHYSICAL_DEVICE_MEMORY_PROPERTIES_HPP
#define _MICRON_ENGINE_RENDERER_VULKAN_VULKAN_PHYSICAL_DEVICE_MEMORY_PROPERTIES_HPP

#include "utility/VulkanUtilities.h"
#include "VulkanMemoryHeap.hpp"

namespace Micron
{
	namespace Vulkan
	{
		class PhysicalDeviceMemoryProperties
		{
		public:
			inline PhysicalDeviceMemoryProperties() noexcept = default;
			inline ~PhysicalDeviceMemoryProperties() noexcept = default;

			constexpr PhysicalDeviceMemoryProperties(VkPhysicalDeviceMemoryProperties const &memoryProperties) noexcept
			{
				heaps.reserve(memoryProperties.memoryHeapCount);
				
				std::ranges::for_each(memoryProperties.memoryHeaps, memoryProperties.memoryHeaps + memoryProperties.memoryHeapCount, [&](auto const &memoryHeap)
				{
					heaps.emplace_back(new MemoryHeap(memoryHeap));
				});
			}

			constexpr USize HeapCount() const noexcept { return heaps.size(); }
			constexpr Vector<Rc<MemoryHeap>> Heaps() const noexcept { return heaps; }
		private:
			Vector<Rc<MemoryHeap>> heaps;
		};
	}
}

#endif