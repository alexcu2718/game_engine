add_subdirectory(camera)

add_library(engine_engine INTERFACE)
target_link_libraries(engine_engine INTERFACE
  engine::camera
)

add_library(engine::engine ALIAS engine_engine)
