#pragma once

#include <vulkan/vulkan.h>

// Macro for standardized vulkan errors for logging
// Maybe something like this?
// #define VK_CHECK(x)                                                        \
//  do {                                                                     \
//    VkResult err = (x);                                                    \
//    if (err != VK_SUCCESS) {                                               \
//      std::cerr << "Vulkan error " << err << " at "                        \
//                << __FILE__ << ":" << __LINE__ << std::endl;               \
//      std::abort();                                                        \
//    }                                                                      \
//  } while (0)
//
