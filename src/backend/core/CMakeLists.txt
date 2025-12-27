add_library(quark_backend_core STATIC 
    vma_impl.cpp
    vk_instance.cpp
    vk_device.cpp
    vk_backend_ctx.cpp
)

target_include_directories(quark_backend_core 
  PUBLIC
    ${CMAKE_SOURCE_DIR}/src     
)

target_link_libraries(quark_backend_core
    PUBLIC
      Vulkan::Vulkan
      GPUOpen::VulkanMemoryAllocator
)

add_library(quark::backend::core ALIAS quark_backend_core)
