add_subdirectory(buffers)
add_subdirectory(descriptors)
add_subdirectory(images)
add_subdirectory(upload)
add_subdirectory(textures)

add_library(engine_resources INTERFACE)
target_link_libraries(engine_resources INTERFACE
  engine::resources::buffers
  engine::resources::descriptors
  engine::resources::images
  engine::resources::upload
  engine::resources::textures
)

add_library(engine::resources ALIAS engine_resources)
