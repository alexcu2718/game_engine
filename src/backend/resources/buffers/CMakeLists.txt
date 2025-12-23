add_library(engine_resources_buffers STATIC 
    vk_buffer.cpp
    vk_per_frame_uniform_buffers.cpp
)

target_include_directories(engine_resources_buffers
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine_resources_buffers
    PUBLIC
        Vulkan::Vulkan
)

add_library(engine::resources::buffers ALIAS engine_resources_buffers)
