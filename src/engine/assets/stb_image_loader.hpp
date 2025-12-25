#pragma once

#include "image_data.hpp"

#include <string>

namespace engine {

bool loadImageRGBA8(const std::string &path, ImageData &out, bool flipY = true);

}
