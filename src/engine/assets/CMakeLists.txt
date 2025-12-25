add_library(engine_assets STATIC 
    stb_image_impl.cpp
    stb_image_loader.cpp
)

target_include_directories(engine_assets
    PUBLIC
      ${CMAKE_SOURCE_DIR}/src
    PRIVATE
      ${Stb_INCLUDE_DIR}
)

add_library(engine::assets ALIAS engine_assets)
