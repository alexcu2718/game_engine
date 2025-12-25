#include "vk_buffer_uploader.hpp"

#include <iostream>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

bool VkBufferUploader::init(VmaAllocator allocator, VkQueue queue,
                            VkCommands *commands) {
  if (allocator == nullptr || queue == VK_NULL_HANDLE || commands == nullptr) {
    std::cerr << "[Uploader] Invalid init args\n";
    return false;
  }

  m_allocator = allocator;
  m_queue = queue;
  m_commands = commands;

  return true;
}

void VkBufferUploader::shutdown() noexcept {
  m_allocator = nullptr;
  m_queue = VK_NULL_HANDLE;
  m_commands = nullptr;
}

bool VkBufferUploader::uploadToDeviceLocalBuffer(const void *data,
                                                 VkDeviceSize size,
                                                 VkBufferUsageFlags finalUsage,
                                                 VkBufferObj &outBuffer) {
  if (m_allocator == nullptr || m_queue == VK_NULL_HANDLE ||
      m_commands == nullptr) {
    std::cerr << "[Uploader] Not initialized\n";
    return false;
  }

  if (data == nullptr || size == 0) {
    std::cerr << "[Uploader] Invalid data or size\n";
    return false;
  }

  // Staging buffer: CPU -> GPU
  // TODO: persist the staging buffer instead of remaking it per upload
  // TODO: make a per-frame upload ring
  VkBufferObj staging{};
  if (!staging.init(m_allocator, size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
                    VkBufferObj::MemUsage::CpuToGpu)) {
    std::cerr << "[Uploader] Failed to create staging buffer\n";
    return false;
  }

  if (!staging.upload(data, size)) {
    std::cerr << "[Uploader] Failed to upload staging data\n";
    return false;
  }

  outBuffer.shutdown();
  if (!outBuffer.init(m_allocator, size,
                      finalUsage | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
                      VkBufferObj::MemUsage::GpuOnly)) {
    std::cerr << "[Uploader] Failed to create index buffer\n";
    return false;
  }

  // TODO: check for transfer queue in queue family and use it
  // TODO: use timeline semaphore values to know when upload is complete
  // instead of offloading submits to a different command buffer
  const bool ok =
      m_commands->submitImmediate(m_queue, [&](VkCommandBuffer cmd) {
        VkBufferCopy region{};
        region.size = size;
        vkCmdCopyBuffer(cmd, staging.handle(), outBuffer.handle(), 1, &region);
      });

  if (!ok) {
    std::cerr << "[Uploader] submitImmediate copy failed\n";
    outBuffer.shutdown();
    return false;
  }

  return true;
}
