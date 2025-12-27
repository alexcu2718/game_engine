add_subdirectory(backend)
add_subdirectory(engine)
add_subdirectory(platform)

add_executable(quark main.cpp)

target_link_libraries(quark
  PRIVATE 
    quark::backend
    quark::engine
    quark::platform
)

