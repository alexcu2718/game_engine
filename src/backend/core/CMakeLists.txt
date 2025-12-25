add_library(engine_core STATIC 
    vma_impl.cpp
    vk_instance.cpp
    vk_device.cpp
    vk_backend_ctx.cpp
)

target_include_directories(engine_core 
  PUBLIC
    ${CMAKE_SOURCE_DIR}/src     
)

target_link_libraries(engine_core
    PUBLIC
      Vulkan::Vulkan
      GPUOpen::VulkanMemoryAllocator
)

add_library(engine::core ALIAS engine_core)
