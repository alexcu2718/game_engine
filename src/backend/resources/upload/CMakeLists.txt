add_library(quark_backend_resources_upload STATIC
    vk_buffer_uploader.cpp
    vk_texture_uploader.cpp
)

target_include_directories(quark_backend_resources_upload
    PUBLIC
      ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(quark_backend_resources_upload
    PUBLIC
      Vulkan::Vulkan
      quark::backend::frame
      GPUOpen::VulkanMemoryAllocator
  quark::backend::resources::textures
)

add_library(quark::backend::resources::upload ALIAS quark_backend_resources_upload)
