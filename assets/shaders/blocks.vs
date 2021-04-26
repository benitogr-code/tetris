#version 330 core

layout (location = 0) in vec2 aPosition;
layout (location = 1) in vec2 aTextureCoord;
layout (location = 2) in vec2 instTranslation;
layout (location = 3) in int  instBlockId;

uniform mat4 u_viewProjection;
uniform vec2 u_blockOffsets[8];

out vec2 v_textCoord;

void main() {
  vec2 position = aPosition + instTranslation;

  v_textCoord = aTextureCoord + u_blockOffsets[instBlockId];
  gl_Position = u_viewProjection * vec4(position.x, position.y, 0.0, 1.0);
}
