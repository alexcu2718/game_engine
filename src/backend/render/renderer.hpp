#pragma once

#include "backend/core/vk_backend_ctx.hpp"
#include "backend/frame/vk_commands.hpp"
#include "backend/frame/vk_frame_manager.hpp"
#include "backend/presentation/vk_presenter.hpp"
#include "backend/resources/buffers/vk_per_frame_uniform_buffers.hpp"
#include "backend/resources/descriptors/vk_material_sets.hpp"
#include "backend/resources/descriptors/vk_per_frame_sets.hpp"
#include "backend/resources/descriptors/vk_shader_interface.hpp"
#include "backend/resources/images/vk_depth_image.hpp"
#include "backend/resources/textures/vk_texture.hpp"
#include "backend/resources/upload/vk_buffer_uploader.hpp"
#include "backend/resources/upload/vk_texture_uploader.hpp"
#include "engine/assets/image_data.hpp"
#include "engine/camera/camera_ubo.hpp"
#include "engine/mesh/vertex.hpp"
#include "mesh_gpu.hpp"
#include "vk_framebuffers.hpp"
#include "vk_pipeline.hpp"
#include "vk_render_pass.hpp"

#include <cstdint>
#include <string>
#include <utility>
#include <vector>
#include <vulkan/vulkan_core.h>

class VkPresenter;
class VkBackendCtx;

struct MeshHandle {
  uint32_t id = 0;
};

struct TextureHandle {
  uint32_t id = UINT32_MAX;
};

class Renderer {
public:
  Renderer() = default;
  ~Renderer() noexcept { shutdown(); }

  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;

  // TODO: redesign uploader's to support rebind without allocation failure
  Renderer(Renderer &&other) noexcept { *this = std::move(other); }
  Renderer &operator=(Renderer &&other) noexcept {
    if (this == &other) {
      return *this;
    }

    shutdown();

    m_ctx = std::exchange(other.m_ctx, nullptr);

    m_framesInFlight = std::exchange(other.m_framesInFlight, 0U);

    m_commands = std::move(other.m_commands);
    m_frames = std::move(other.m_frames);

    m_interface = std::move(other.m_interface);
    m_cameraUbo = other.m_cameraUbo;

    m_perFrameBufs = std::move(other.m_perFrameBufs);
    m_perFrameSets = std::move(other.m_perFrameSets);

    m_textureUploader = std::move(other.m_textureUploader);
    m_textures = std::move(other.m_textures);
    m_materials = std::move(other.m_materials);
    m_activeMaterial = std::exchange(other.m_activeMaterial, UINT32_MAX);

    m_uploader = std::move(other.m_uploader);
    m_meshes = std::move(other.m_meshes);

    // Fix uploader pointer to refer to this renderer's commands
    m_uploader.init(m_ctx->allocator(), m_ctx->graphicsQueue(), &m_commands);

    m_renderPass = std::move(other.m_renderPass);
    m_pipeline = std::move(other.m_pipeline);
    m_framebuffers = std::move(other.m_framebuffers);

    m_vertPath = std::exchange(other.m_vertPath, {});
    m_fragPath = std::exchange(other.m_fragPath, {});
    return *this;
  }

  bool init(VkBackendCtx &ctx, VkPresenter &presenter, uint32_t framesInFlight,
            const std::string &vertSpvPath, const std::string &fragSpvPath);
  void shutdown() noexcept;

  MeshHandle createMesh(const engine::Vertex *vertices, uint32_t vertexCount,
                        const uint32_t *indices, uint32_t indexCount);
  [[nodiscard]] const MeshGpu *mesh(MeshHandle handle) const;

  [[nodiscard]] bool drawFrame(VkPresenter &presenter, MeshHandle mesh);

  bool recreateSwapchainDependent(VkPresenter &presenter,
                                  const std::string &vertSpvPath,
                                  const std::string &fragSpvPath);

  void setCameraUBO(const CameraUBO &ubo) { m_cameraUbo = ubo; }

  bool createTextureFromImage(const engine::ImageData &img,
                              VkTexture2D &outTex);
  TextureHandle createTextureFromFile(const std::string &path, bool flipY);
  uint32_t createMaterialFromTexture(TextureHandle textureHandle);
  void setActiveMaterial(uint32_t materialIndex);

private:
  void recordFrame(VkCommandBuffer cmd, VkFramebuffer fb, VkExtent2D extent,
                   const MeshGpu &mesh);

  // Todo delete: test rotations
  float m_timeSeconds = 0.0F;

  VkBackendCtx *m_ctx = nullptr; // non-owning

  uint32_t m_framesInFlight = 0;

  VkCommands m_commands;
  VkFrameManager m_frames;

  VkShaderInterface m_interface;
  VkPerFrameUniformBuffers m_perFrameBufs;
  VkPerFrameSets m_perFrameSets;
  CameraUBO m_cameraUbo{};

  std::vector<VkTexture2D> m_textures;
  VkMaterialSets m_materials;
  uint32_t m_activeMaterial = UINT32_MAX;
  VkTextureUploader m_textureUploader;

  std::vector<MeshGpu> m_meshes;
  VkBufferUploader m_uploader;

  VkRenderPassObj m_renderPass;
  VkGraphicsPipeline m_pipeline;
  VkFramebuffers m_framebuffers;

  VkDepthImage m_depth;

  std::string m_vertPath;
  std::string m_fragPath;
};
