#pragma once

#include "backend/render/renderer.hpp"

#include <cstdint>
#include <vector>

namespace engine {

struct GltfDrawItem {
  MeshHandle mesh{};
  uint32_t material = UINT32_MAX;
};

struct GltfScene {
  std::vector<GltfDrawItem> items;
};

bool loadGltfScene(Renderer &renderer, const std::string &gltfPath,
                   GltfScene &out, bool flipTextureY = false);

} // namespace engine
