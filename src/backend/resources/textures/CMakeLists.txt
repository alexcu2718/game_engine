add_library(engine_resources_textures STATIC 
    vk_texture_utils.cpp
)

target_include_directories(engine_resources_textures
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine_resources_textures
    PUBLIC
        Vulkan::Vulkan
)

add_library(engine::resources::textures ALIAS engine_resources_textures)
