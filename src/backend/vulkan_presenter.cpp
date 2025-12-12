#include "vulkan_presenter.hpp"
#include "vulkan_context.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vulkan/vulkan_core.h>

bool VulkanPresenter::init(VulkanContext &ctx, GLFWwindow *window,
                           uint32_t width, uint32_t height) {
  if (!window) {
    std::cerr << "[Presenter] window is null\n";
    return false;
  }

  if (ctx.instance() == VK_NULL_HANDLE) {
    std::cerr << "[Presenter] ctx.instance() is null\n";
    return false;
  }

  // If re-init, shut down existing resources first
  shutdown(ctx);

  VkResult surfRes =
      glfwCreateWindowSurface(ctx.instance(), window, nullptr, &m_surface);
  if (surfRes != VK_SUCCESS) {
    std::cerr << "[Presenter] glfwCreateWindowSurface failed: " << surfRes
              << "\n";
    m_surface = VK_NULL_HANDLE;
    return false;
  }

  if (!m_swapchain.init(ctx.physicalDevice(), ctx.device(), m_surface, width,
                        height, ctx.graphicsQueueFamilyIndex())) {
    std::cerr << "[Presenter] swapchain init failed\n";
    vkDestroySurfaceKHR(ctx.instance(), m_surface, nullptr);
    m_surface = VK_NULL_HANDLE;
    return false;
  }

  if (!m_swapchain.createSwapchainImageViews(ctx.device())) {
    std::cerr << "[Presenter] swapchain image views creation failed\n";
    m_swapchain.shutdown(ctx.device());
    vkDestroySurfaceKHR(ctx.instance(), m_surface, nullptr);
    m_surface = VK_NULL_HANDLE;
    return false;
  }

  return true;
}

void VulkanPresenter::shutdown(VulkanContext &ctx) {
  if (ctx.device() != VK_NULL_HANDLE) {
    m_swapchain.shutdown(ctx.device());
  }

  if (m_surface != VK_NULL_HANDLE) {
    VkInstance instance = ctx.instance();
    if (instance != VK_NULL_HANDLE) {
      vkDestroySurfaceKHR(instance, m_surface, nullptr);
    }
    m_surface = VK_NULL_HANDLE;
  }
}
