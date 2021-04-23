#version 330 core

layout (location = 0) in vec2 in_position;
layout (location = 1) in vec2 in_textCoord;

uniform mat4 u_viewProjection;

out vec2 v_textCoord;

void main() {
  v_textCoord = in_textCoord;
  gl_Position = u_viewProjection * vec4(in_position.x, in_position.y, 0.0, 1.0);
}
