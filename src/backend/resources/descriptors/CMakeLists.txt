add_library(engine_resources_descriptors STATIC 
    vk_material_sets.cpp
    vk_per_frame_sets.cpp
    vk_shader_interface.cpp
)

target_include_directories(engine_resources_descriptors
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(engine_resources_descriptors
    PUBLIC
        Vulkan::Vulkan
        glm::glm
)

add_library(engine::resources::descriptors ALIAS engine_resources_descriptors)
