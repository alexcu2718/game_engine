add_library(backend STATIC 
    vulkan_context.cpp
    vulkan_context.hpp
)

target_include_directories(backend
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(backend
    PUBLIC
        Vulkan::Vulkan
)
