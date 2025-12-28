#include "backend/presentation/vk_presenter.hpp"
#include "backend/render/renderer.hpp"
#include "engine/app/app.hpp"
#include "engine/assets/gltf/gltf_gpu_builder.hpp"
#include "engine/camera/camera.hpp"
#include "platform/input/camera_controller.hpp"
#include <engine/assets/gltf/gltf_cpu_loader.hpp>

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/vector_float3.hpp>
#include <iostream>
#include <vulkan/vulkan_core.h>

int main() {
  EngineApp app;
  AppConfig cfg{};
  cfg.title = "Hello Window";

  if (!app.init(cfg)) {
    std::cerr << "App init failed\n";
    return 1;
  }

  Camera camera;
  CameraController controller(app.window(), &camera);
  controller.enableCursorCapture(true);

  // auto cube = app.meshes().cube();

  engine::assets::GltfSceneCpu gltfCpu;
  engine::assets::GltfLoadOptions opt{};
  opt.flipTexcoordV = true;
  opt.axis.yUpToZUp = true;
  opt.axis.flipAxisZ = true;

  // TODO: make cleaner API
  if (!engine::assets::loadGltfCpu("assets/tree2.glb", gltfCpu, opt)) {
    std::cerr << "Failed to load gltf\n";
    return 1;
  }

  engine::assets::GltfSceneGpu gltfGpu;
  if (!engine::assets::buildGltfSceneGpu(app.renderer(), "assets/tree2.glb",
                                         gltfCpu, gltfGpu)) {
    std::cerr << "Failed to build gltf GPU scene\n";
    return 1;
  }

  // auto texture = app.renderer().createTextureFromFile("assets/terry.jpg",
  // true); uint32_t material =
  // app.renderer().createMaterialFromTexture(texture);

  app.run([&](float dt) {
    controller.update(dt);
    app.renderer().setCameraUBO(camera.makeUbo(app.presenter().extent()));

    // const float t = (float)glfwGetTime();

    // std::array<DrawItem, 2> items{};
    // items[0].mesh = cube;
    // items[0].material = material;
    // items[0].model = engine::makeModel({-1, 0, 0}, {0, 0, t});
    //
    // // TODO: add instances
    // items[1].mesh = cube;
    // items[1].material = material;
    // items[1].model = engine::makeModel({+1, 0, 0}, {0, 0, -t});

    // (void)app.renderer().drawFrame(app.presenter(), items);
    (void)app.renderer().drawFrame(app.presenter(), gltfGpu.drawItems);
  });

  return 0;
}
