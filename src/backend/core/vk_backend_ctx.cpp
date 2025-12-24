#include "vk_backend_ctx.hpp"

#include <iostream>
#include <span>

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

  return true;
}

void VkBackendCtx::shutdown() noexcept {

  m_device.shutdown();
  m_instance.shutdown();
}
