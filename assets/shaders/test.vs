#version 410 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec2 inTextCoord;

out vec2 TextCoord;

void main() {
  TextCoord = inTextCoord;
  gl_Position = vec4(inPos.x, inPos.y, inPos.z, 1.0);
}
