#include "vk_image.hpp"

#include "../buffers/vk_memory_utils.hpp"

#include <cstdint>
#include <iostream>
#include <vulkan/vulkan_core.h>

bool VkImageObj::init2D(VkPhysicalDevice physicalDevice, VkDevice device,
                        uint32_t width, uint32_t height, VkFormat format,
                        VkImageUsageFlags usage, VkMemoryPropertyFlags memProps,
                        VkImageTiling tiling) {
  if (physicalDevice == VK_NULL_HANDLE || device == VK_NULL_HANDLE ||
      width == 0 || height == 0 || format == VK_FORMAT_UNDEFINED) {
    std::cerr << "[Image] init2D invalid args\n";
    return false;
  }

  // Re-init
  shutdown();

  m_device = device;
  m_format = format;
  m_width = width;
  m_height = height;

  VkImageCreateInfo imageInfo{};
  imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent = VkExtent3D{width, height, 1U};
  imageInfo.mipLevels = 1; // Todo: add mipmap
  imageInfo.arrayLayers = 1;
  imageInfo.format = format;
  imageInfo.tiling = tiling;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = usage;
  imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
  imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  VkResult res = vkCreateImage(m_device, &imageInfo, nullptr, &m_image);
  if (res != VK_SUCCESS) {
    std::cerr << "[Image] vkCreateImage failed: " << res << "\n";
    shutdown();
    return false;
  }

  VkMemoryRequirements memReq{};
  vkGetImageMemoryRequirements(m_device, m_image, &memReq);

  uint32_t memIndex = 0;
  if (!vkFindMemoryTypeIndex(physicalDevice, memReq.memoryTypeBits, memProps,
                             memIndex)) {
    std::cerr << "[Image] No suitable memory type\n";
    shutdown();
    return false;
  }

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memReq.size;
  allocInfo.memoryTypeIndex = memIndex;

  res = vkAllocateMemory(m_device, &allocInfo, nullptr, &m_memory);
  if (res != VK_SUCCESS) {
    std::cerr << "[Image] vkBindImageMemory failed: " << res << "\n";
    shutdown();
    return false;
  }

  res = vkBindImageMemory(device, m_image, m_memory, 0);
  if (res != VK_SUCCESS) {
    std::cerr << "[Image] vkBindImageMemory failed: " << res << "\n";
    shutdown();
    return false;
  }

  return true;
}

void VkImageObj::shutdown() noexcept {
  if (m_device != VK_NULL_HANDLE) {
    if (m_image != VK_NULL_HANDLE) {
      vkDestroyImage(m_device, m_image, nullptr);
    }

    if (m_memory != VK_NULL_HANDLE) {
      vkFreeMemory(m_device, m_memory, nullptr);
    }
  }

  m_image = VK_NULL_HANDLE;
  m_memory = VK_NULL_HANDLE;
  m_format = VK_FORMAT_UNDEFINED;
  m_width = 0;
  m_height = 0;
  m_device = VK_NULL_HANDLE;
}
