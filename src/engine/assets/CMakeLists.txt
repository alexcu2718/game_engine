add_library(quark_engine_assets STATIC
    stb_image_impl.cpp
    stb_image_loader.cpp
)

target_include_directories(quark_engine_assets
    PUBLIC
      ${CMAKE_SOURCE_DIR}/src
      quark::backend::renderer
    PRIVATE
      ${Stb_INCLUDE_DIR}
      # ${CGLTF_INCLUDE_DIRS}
)

add_library(quark::engine::assets ALIAS quark_engine_assets)
