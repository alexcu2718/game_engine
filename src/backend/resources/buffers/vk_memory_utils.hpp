#pragma once

#include <cstdint>
#include <vulkan/vulkan_core.h>

inline bool vkFindMemoryTypeIndex(VkPhysicalDevice physicalDevice,
                                  uint32_t typeBits,
                                  VkMemoryPropertyFlags props,
                                  uint32_t &outIndex) {
  VkPhysicalDeviceMemoryProperties memProps{};
  vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProps);

  for (uint32_t i = 0; i < memProps.memoryTypeCount; ++i) {
    const uint32_t bit = (1U << i);
    const bool typeOk = (typeBits & bit) != 0;
    const bool propsOk =
        (memProps.memoryTypes[i].propertyFlags & props) == props;
    if (typeOk && propsOk) {
      outIndex = i;
      return true;
    }
  }

  return false;
}
