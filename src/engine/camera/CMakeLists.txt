add_library(quark_engine_camera STATIC 
    camera.cpp
)

target_include_directories(quark_engine_camera
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(quark_engine_camera
    PUBLIC
        Vulkan::Vulkan
        glm::glm
)

add_library(quark::engine::camera ALIAS quark_engine_camera)
