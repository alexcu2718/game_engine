add_library(backend STATIC 
    vulkan_context.cpp
    vulkan_context.hpp
    vulkan_swapchain.cpp
    vulkan_swapchain.hpp
    vulkan_presenter.cpp
    vulkan_presenter.hpp
    vulkan_shader.cpp
    vulkan_shader.hpp
)

target_include_directories(backend
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(backend
    PUBLIC
        Vulkan::Vulkan
    PRIVATE
        glfw
)
