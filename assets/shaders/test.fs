#version 410 core

in vec2 TextCoord;

uniform sampler2D aTexture;

out vec4 FragColor;

void main() {
  FragColor = texture(aTexture, TextCoord);
}
