#version 330 core

in vec2 v_textCoord;

uniform sampler2D u_texture;

out vec4 FragColor;

void main() {
  FragColor = texture(u_texture, v_textCoord);
}
