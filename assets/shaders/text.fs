#version 330 core

in vec2 v_textCoord;

uniform sampler2D u_texture;
uniform vec3      u_textColor;

out vec4 FragColor;

void main() {
  vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, v_textCoord).r);
  FragColor = vec4(u_textColor, 1.0) * sampled;
}
