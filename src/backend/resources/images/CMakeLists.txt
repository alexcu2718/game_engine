add_library(quark_backend_resources_images STATIC 
    vk_image.cpp
    vk_depth_image.cpp
)

target_include_directories(quark_backend_resources_images
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(quark_backend_resources_images
    PUBLIC
        Vulkan::Vulkan
        GPUOpen::VulkanMemoryAllocator
)

add_library(quark::backend::resources::images ALIAS quark_backend_resources_images)
