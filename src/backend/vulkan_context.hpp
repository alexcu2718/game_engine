#pragma once

#include <cstdint>
#include <optional>
#include <vector>
#include <vulkan/vulkan.h>

class VulkanContext {
public:
  VulkanContext();
  ~VulkanContext();

  bool init(const std::vector<const char *>
                &platformExtensions); // Create instance and debug messenger
  void shutdown();                    // Destroy in reverse order

  VkInstance instance() const { return m_instance; }
  VkPhysicalDevice physicalDevice() const { return m_physicalDevice; }
  VkDevice device() const { return m_device; }
  VkQueue graphicsQueue() const { return m_graphicsQueue; }
  uint32_t graphicsQueueFamilyIndex() const {
    return m_graphicsQueueFamilyIndex;
  }

private:
  bool checkValidationLayerSupport();
  bool createInstance(const std::vector<const char *> &platformExtensions);
  bool setupDebugMessenger();

  bool pickPhysicalDevice();
  bool createLogicalDevice();

  struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() const { return graphicsFamily.has_value(); }
  };

  QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
  bool checkDeviceExtensionSupport(VkPhysicalDevice device);

  VkInstance m_instance = VK_NULL_HANDLE;
  VkDebugUtilsMessengerEXT m_debugMessenger = VK_NULL_HANDLE;

  VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
  VkDevice m_device = VK_NULL_HANDLE;
  VkQueue m_graphicsQueue = VK_NULL_HANDLE;
  uint32_t m_graphicsQueueFamilyIndex = UINT32_MAX;

  bool m_enableValidationLayers = true; // Gated by NDEBUG in cpp
};
