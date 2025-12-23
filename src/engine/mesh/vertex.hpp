#pragma once

#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"

namespace engine {

struct Vertex {
  glm::vec3 pos;
  glm::vec3 color;
  glm::vec2 uv;
};

static_assert(sizeof(Vertex) == sizeof(float) * 8);

} // namespace engine
