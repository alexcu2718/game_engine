add_library(engine_resources_texture STATIC 
    vk_image.cpp
    vk_texture_uploader.cpp
    vk_texture_utils.cpp
)

target_include_directories(engine_resources_texture
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine_resources_texture
    PUBLIC
        Vulkan::Vulkan
)

add_library(engine::resources::texture ALIAS engine_resources_texture)
