add_subdirectory(buffers)
add_subdirectory(descriptors)
add_subdirectory(images)
add_subdirectory(upload)
add_subdirectory(textures)

add_library(engine_resources INTERFACE)
target_link_libraries(engine_resources INTERFACE
  quark::backend::resources::buffers
  quark::backend::resources::descriptors
  quark::backend::resources::images
  quark::backend::resources::textures
  quark::backend::resources::upload
)

add_library(engine::resources ALIAS engine_resources)
