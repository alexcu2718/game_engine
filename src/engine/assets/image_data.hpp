#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace engine {

struct ImageData {
  uint32_t width = 0;
  uint32_t height = 0;
  uint32_t channels = 0;
  // Fun: change to uint16_t
  std::vector<uint8_t> pixels; // size = width * height * 4
  [[nodiscard]] bool valid() const noexcept {
    return width > 0 && height > 0 &&
           pixels.size() == static_cast<size_t>(width) * height * 4;
  }
};

} // namespace engine
