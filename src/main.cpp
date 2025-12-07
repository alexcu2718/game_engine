#include "backend/vulkan_context.hpp"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vulkan/vulkan_core.h>

int main() {
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return 1;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  // Get needed GLFW instance extensions
  uint32_t glfwExtCount = 0;
  const char **glfwExts = glfwGetRequiredInstanceExtensions(&glfwExtCount);
  if (!glfwExts || glfwExtCount == 0) {
    std::cerr << "glfwGetRequiredInstanceExtensions returned nothins\n";
    glfwTerminate();
    return 1;
  }

  std::vector<const char *> platformExtensions(glfwExts,
                                               glfwExts + glfwExtCount);

  VulkanContext ctx;
  if (!ctx.init(platformExtensions)) {
    std::cerr << "Failed to initialize Vulkan\n";
    glfwTerminate();
    return 1;
  }

  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Hello Window", nullptr, nullptr);
  if (!window) {
    std::cerr << "Failed to create window\n";
    ctx.shutdown();
    glfwTerminate();
    return 1;
  }

  // Create VkSurfaceKHR
  VkSurfaceKHR surface = VK_NULL_HANDLE;
  VkResult surfRes =
      glfwCreateWindowSurface(ctx.instance(), window, nullptr, &surface);
  if (surfRes != VK_SUCCESS) {
    std::cerr << "Failed to create window surface, error " << surfRes << "\n";
    glfwDestroyWindow(window);
    ctx.shutdown();
    glfwTerminate();
    return 1;
  }

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    // Rendering
  }

  vkDeviceWaitIdle(ctx.device());

  vkDestroySurfaceKHR(ctx.instance(), surface, nullptr);
  glfwDestroyWindow(window);
  glfwTerminate();

  // TODO: swapchain

  ctx.shutdown();
  return 0;
}
