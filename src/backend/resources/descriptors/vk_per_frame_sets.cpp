#include "vk_per_frame_sets.hpp"

#include "backend/resources/buffers/vk_per_frame_uniform_buffers.hpp"

#include <cstdint>
#include <iostream>
#include <vulkan/vulkan_core.h>

bool VkPerFrameSets::init(VkDevice device, VkDescriptorSetLayout layout,
                          const VkPerFrameUniformBuffers &bufs) {
  if (device == VK_NULL_HANDLE || layout == VK_NULL_HANDLE || !bufs.valid()) {
    std::cerr << "[PerFrameSets] init invalid args\n";
    return false;
  }

  shutdown();
  m_device = device;

  const uint32_t framesInFlight = bufs.frameCount();

  VkDescriptorPoolSize poolSize{};
  poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  poolSize.descriptorCount = framesInFlight;

  VkDescriptorPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  poolInfo.maxSets = framesInFlight;
  poolInfo.poolSizeCount = 1;
  poolInfo.pPoolSizes = &poolSize;

  VkResult res = vkCreateDescriptorPool(m_device, &poolInfo, nullptr, &m_pool);
  if (res != VK_SUCCESS) {
    std::cerr << "[PerFrameSets] vkCreateDescriptorPool failed: " << res
              << "\n";
    shutdown();
    return false;
  }

  std::vector<VkDescriptorSetLayout> layouts(framesInFlight, layout);

  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = m_pool;
  allocInfo.descriptorSetCount = framesInFlight;
  allocInfo.pSetLayouts = layouts.data();

  m_sets.resize(framesInFlight);
  res = vkAllocateDescriptorSets(m_device, &allocInfo, m_sets.data());
  if (res != VK_SUCCESS) {
    std::cerr << "[PerFrameSets] Failed to allocate descriptor sets\n";
    shutdown();
    return false;
  }

  // Write binding 0 for each frame
  for (uint32_t i = 0; i < framesInFlight; ++i) {
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = bufs.buffer(i).handle();
    bufferInfo.offset = 0;
    bufferInfo.range = bufs.stride();

    VkWriteDescriptorSet write{};
    write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    write.dstSet = m_sets[i];
    write.dstBinding = 0;
    write.descriptorCount = 1;
    write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    write.pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(m_device, 1, &write, 0, nullptr);
  }

  return true;
}

void VkPerFrameSets::shutdown() noexcept {
  if (m_device != VK_NULL_HANDLE && m_pool != VK_NULL_HANDLE) {
    vkDestroyDescriptorPool(m_device, m_pool, nullptr);
  }

  m_pool = VK_NULL_HANDLE;
  m_sets.clear();
  m_device = VK_NULL_HANDLE;
}

void VkPerFrameSets::bind(VkCommandBuffer cmd, VkPipelineLayout pipelineLayout,
                          uint32_t setIndex, uint32_t frameIndex) const {
  if (frameIndex >= m_sets.size()) {
    return;
  }

  VkDescriptorSet set = m_sets[frameIndex];

  // TODO: use dynamic offset to have on descriptor per object UBO ring buffer
  vkCmdBindDescriptorSets(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout,
                          setIndex, 1, &set, 0, nullptr);
}
