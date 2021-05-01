#version 330 core

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_textureCoord;

uniform mat4 u_viewProjection;

out vec2 v_textCoord;

void main() {
  v_textCoord = a_textureCoord;
  gl_Position = u_viewProjection * vec4(a_position.x, a_position.y, 0.0, 1.0);
}
