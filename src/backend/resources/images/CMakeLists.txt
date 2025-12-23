add_library(engine_resources_images STATIC 
    vk_image.cpp
    vk_depth_image.cpp
)

target_include_directories(engine_resources_images
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine_resources_images
    PUBLIC
        Vulkan::Vulkan
)

add_library(engine::resources::images ALIAS engine_resources_images)
