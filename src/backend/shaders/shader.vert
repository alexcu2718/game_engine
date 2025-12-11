#version 450

// Per-vertex color
layout(location = 0) out vec3 vColor;

// TODO: Make vertex buffer so no hard-coding
const vec2 POSITIONS[3] = vec2[](
  vec2( 0.0, -0.5), // bottom
  vec2( 0.5,  0.5), // top right
  vec2(-0.5,  0.5)  // top left
);

const vec3 COLORS[3] = vec3[](
  vec3(1.0, 0.0, 0.0), // red
  vec3(0.0, 1.0, 0.0), // green
  vec3(0.0, 0.0, 1.0)  // blue
);

void main() {
  gl_Position = vec4(POSITIONS[gl_VertexIndex], 0.0, 1.0);
  vColor = COLORS[gl_VertexIndex];
}
