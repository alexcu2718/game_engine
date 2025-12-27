#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>

namespace engine {

inline glm::mat4 makeModel(glm::vec3 pos = {0, 0, 0},
                           glm::vec3 rotRad = {0, 0, 0},
                           glm::vec3 scale = {1, 1, 1}) {
  glm::mat4 m(1.0F);
  m = glm::translate(m, pos);

  m = glm::rotate(m, rotRad.z, glm::vec3(0, 0, 1));
  m = glm::rotate(m, rotRad.y, glm::vec3(0, 1, 0));
  m = glm::rotate(m, rotRad.x, glm::vec3(1, 0, 0));

  m = glm::scale(m, scale);
  return m;
}

} // namespace engine
