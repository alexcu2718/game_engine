#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inUV;

layout(location = 0) out vec3 vColor;
layout(location = 1) out vec2 v_uv;

layout(set = 0, binding = 0) uniform CameraUBO {
  mat4 view;
  mat4 proj;
} camera;

layout(push_constant) uniform Push {
  mat4 model;
} push;

void main() {
  gl_Position = camera.proj * camera.view * push.model * vec4(inPos, 1.0);
  v_uv = inUV;
  vColor = inColor;
}
