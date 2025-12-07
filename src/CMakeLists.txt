add_executable(main main.cpp)
add_subdirectory(backend)

target_link_libraries(main 
  PRIVATE 
      glfw
      backend
)
