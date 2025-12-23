include(FetchContent)

# GLFW3
FetchContent_Declare(
  glfw 
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# GLM
FetchContent_Declare(
  glm 
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 1.0.2
)
FetchContent_MakeAvailable(glm)


# stb_image
FetchContent_Declare(
  stb
  GIT_REPOSITORY https://github.com/nothings/stb
  GIT_TAG master
)
FetchContent_MakeAvailable(stb)

add_library(stb_image STATIC stb_image_impl.cpp)
target_include_directories(stb_image PUBLIC ${stb_SOURCE_DIR})

add_library(engine_third_party INTERFACE)

target_include_directories(engine_third_party
    INTERFACE 
       glfw 
       glm
       stb_image
)

add_library(engine::third_party ALIAS engine_third_party)
