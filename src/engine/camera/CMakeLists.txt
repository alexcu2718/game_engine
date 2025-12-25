add_library(engine_camera STATIC 
    camera.cpp
)

target_include_directories(engine_camera
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(engine_camera
    PUBLIC
        Vulkan::Vulkan
        glm::glm
)

add_library(engine::camera ALIAS engine_camera)
