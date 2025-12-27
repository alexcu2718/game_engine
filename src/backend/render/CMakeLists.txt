add_library(quark_backend_render STATIC
    renderer.cpp
    vk_framebuffers.cpp
    vk_pipeline.cpp
    vk_render_pass.cpp
)

target_include_directories(quark_backend_render
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(quark_backend_render
    PUBLIC
        quark::backend::frame
        quark::backend::presentation
        quark::backend::core
    quark::backend::resources::upload
    quark::engine::assets
        quark::backend::shaders
        Vulkan::Vulkan
        glm::glm
)

add_library(quark::backend::render ALIAS quark_backend_render)
