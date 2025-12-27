// #include "glm/ext/vector_float2.hpp"
//
// #include <cgltf.h>
// #include <filesystem>
// #include <glm/ext/vector_float3.hpp>
// #include <string>
//
// namespace engine {
//
// static bool readVec3(const cgltf_accessor *acc, cgltf_size i, glm::vec3 &out)
// {
//   float v[3] = {0, 0, 0};
//   if (!cgltf_accessor_read_float(acc, i, v, 3)) {
//     return false;
//   }
//
//   out = glm::vec3{v[0], v[1], v[2]};
//   return true;
// }
//
// static bool readVec2(const cgltf_accessor *acc, cgltf_size i, glm::vec2 &out)
// {
//   float v[2] = {0, 0};
//   if (!cgltf_accessor_read_float(acc, i, v, 2)) {
//     return false;
//   }
//
//   out = glm::vec2{v[0], v[1]};
//   return true;
// }
//
// static const cgltf_accessor *findAttribute(const cgltf_primitive &primitive,
//                                            cgltf_attribute_type type,
//                                            cgltf_int index = 0) {
//   for (cgltf_size a = 0; a < primitive.attributes_count; ++a) {
//     const cgltf_attribute &attr = primitive.attributes[a];
//     if (attr.type == type && attr.index == index) {
//       return attr.data;
//     }
//   }
//
//   return nullptr;
// }
//
// static std::string resolveUriPath(const std::filesystem::path &baseDir,
//                                   const char *uri) {
//   if (!uri || uri[0] == '\0') {
//     return {};
//   }
//
//   // TODO: handle URIs
//   std::string s(uri);
//   if (s.rfind("data: ", 0) == 0) {
//     return {};
//   }
//
//   std::filesystem::path p = baseDir / std::filesystem::path(s);
//
//   return p.lexically_normal().string();
// }
//
// // static uint32_t buildMaterial(Renderer &renderer,
// //                               const std::filesystem::path &baseDir,
// //                               const cgltf_material *mat, bool
// flipTextureY)
// //                               {}
// //
// } // namespace engine
