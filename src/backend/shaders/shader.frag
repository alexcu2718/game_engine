#version 450

layout(set=1, binding=0) uniform sampler2D u_baseColor;
layout(location = 0) in vec3 v_color;
layout(location = 1) in vec2 v_uv;
layout(location = 0) out vec4 outColor;

void main() {
  vec4 tex = texture(u_baseColor, v_uv);
  outColor = tex;
}
