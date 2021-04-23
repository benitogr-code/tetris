#version 330 core

in vec2 v_textCoord;

uniform sampler2D aTexture;

out vec4 FragColor;

void main() {
  FragColor = texture(aTexture, v_textCoord);
}
