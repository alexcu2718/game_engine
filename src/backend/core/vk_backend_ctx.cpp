#include "vk_backend_ctx.hpp"

#include <iostream>
#include <span>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

bool VkBackendCtx::init(std::span<const char *const> platformExtensions,
                        bool enableValidation) {
  shutdown();

  if (!m_instance.init(platformExtensions, enableValidation)) {
    std::cerr << "[Core] VkInstance init failed\n";
    shutdown();
    return false;
  }

  if (!m_device.init(m_instance.instance())) {
    std::cerr << "[Core] VkDevice init failed\n";
    shutdown();
    return false;
  }

  if (!createAllocator()) {
    std::cerr << "[Core] VMA allocator init failed\n";
    shutdown();
    return false;
  }

  return true;
}

void VkBackendCtx::shutdown() noexcept {
  if (m_allocator != nullptr) {
    vmaDestroyAllocator(m_allocator);
    m_allocator = nullptr;
  }

  m_device.shutdown();
  m_instance.shutdown();
}

bool VkBackendCtx::createAllocator() {
  VmaAllocatorCreateInfo vmaInfo{};
  vmaInfo.instance = m_instance.instance();
  vmaInfo.physicalDevice = m_device.physicalDevice();
  vmaInfo.device = m_device.device();

  const VkResult res = vmaCreateAllocator(&vmaInfo, &m_allocator);
  if (res != VK_SUCCESS) {
    std::cerr << "[Core] vmaCreateAllocator failed: " << res << "\n";
    m_allocator = nullptr;
    return false;
  }

  return true;
}
