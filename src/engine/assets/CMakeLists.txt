add_library(engine_assets STATIC 
    stb_image_loader.cpp
)

target_include_directories(engine_assets
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine_assets
    PUBLIC
      stb_image
)

add_library(engine::assets ALIAS engine_assets)
