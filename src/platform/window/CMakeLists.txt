add_library(quark_platform_window STATIC 
    glfw_window.cpp
)

target_include_directories(quark_platform_window
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(quark_platform_window
    PUBLIC
      glfw
      Vulkan::Vulkan
)

add_library(quark::platform::window ALIAS quark_platform_window)
