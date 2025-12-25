#pragma once

#include "vk_device.hpp"
#include "vk_instance.hpp"

#include <cstdint>
#include <span>
#include <utility>
#include <vk_mem_alloc.h>
#include <vulkan/vulkan_core.h>

class VkBackendCtx {
public:
  VkBackendCtx() = default;
  ~VkBackendCtx() noexcept { shutdown(); }

  VkBackendCtx(const VkBackendCtx &) = delete;
  VkBackendCtx &operator=(const VkBackendCtx &) = delete;

  VkBackendCtx(VkBackendCtx &&other) noexcept { *this = std::move(other); }
  VkBackendCtx &operator=(VkBackendCtx &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    shutdown();

    m_instance = std::move(other.m_instance);
    m_device = std::move(other.m_device);

    return *this;
  }

  bool init(std::span<const char *const> platformExtensions,
            bool enableValidation);
  void shutdown() noexcept;

  [[nodiscard]] VkInstance instance() const noexcept {
    return m_instance.instance();
  }
  [[nodiscard]] VkPhysicalDevice physicalDevice() const noexcept {
    return m_device.physicalDevice();
  }
  [[nodiscard]] VkDevice device() const noexcept { return m_device.device(); }
  [[nodiscard]] const VkQueues &queues() const noexcept {
    return m_device.queues();
  }
  [[nodiscard]] uint32_t graphicsQueueFamily() const noexcept {
    return m_device.queues().graphicsFamily;
  }
  [[nodiscard]] VkQueue graphicsQueue() const noexcept {
    return m_device.queues().graphics;
  }

  [[nodiscard]] VmaAllocator allocator() const noexcept { return m_allocator; }

private:
  [[nodiscard]] bool createAllocator();

  VkInstanceCtx m_instance;
  VkDeviceCtx m_device;
  VmaAllocator m_allocator = nullptr;
};
