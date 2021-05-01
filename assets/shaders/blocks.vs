#version 330 core

layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_textureCoord;
layout (location = 2) in vec2 a_translation;
layout (location = 3) in int  a_blockId;

uniform mat4 u_viewProjection;
uniform vec2 u_blockOffsets[8];

out vec2 v_textCoord;

void main() {
  vec2 position = a_position + a_translation;

  v_textCoord = a_textureCoord + u_blockOffsets[a_blockId];
  gl_Position = u_viewProjection * vec4(position.x, position.y, 0.0, 1.0);
}
