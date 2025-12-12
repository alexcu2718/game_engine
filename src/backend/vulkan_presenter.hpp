#pragma once

#include "vulkan_swapchain.hpp"
#include <cstdint>
#include <vector>
#include <vulkan/vulkan_core.h>

struct GLFWwindow;
class VulkanContext;

// Owns VulkanSwapchain and VkSurfaceKHR
class VulkanPresenter {
public:
  VulkanPresenter() = default;
  ~VulkanPresenter() = default;

  VulkanPresenter(const VulkanPresenter &) = delete;
  VulkanPresenter &operator=(const VulkanPresenter &) = delete;

  bool init(VulkanContext &ctx, GLFWwindow *window, uint32_t width,
            uint32_t height);
  void shutdown(VulkanContext &ctx);

  VkFormat imageFormat() const { return m_swapchain.swapchainImageFormat(); }
  VkExtent2D extent() const { return m_swapchain.swapchainExtent(); }
  const std::vector<VkImageView> &imageViews() const {
    return m_swapchain.swapchainImageViews();
  }
  VkSwapchainKHR swapchain() const { return m_swapchain.swapchain(); }

  VkSurfaceKHR surface() const { return m_surface; }
  bool isInitialized() const { return m_surface != VK_NULL_HANDLE; }

private:
  VkSurfaceKHR m_surface = VK_NULL_HANDLE;
  VulkanSwapchain m_swapchain;
};
