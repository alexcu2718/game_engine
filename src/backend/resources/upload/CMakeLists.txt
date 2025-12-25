add_library(engine_resources_upload STATIC 
    vk_buffer_uploader.cpp
    vk_texture_uploader.cpp
)

target_include_directories(engine_resources_upload
    PUBLIC
      ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(engine_resources_upload
    PUBLIC
      Vulkan::Vulkan
      engine::frame
      # engine::resources::buffers
      GPUOpen::VulkanMemoryAllocator
)

add_library(engine::resources::upload ALIAS engine_resources_upload)
