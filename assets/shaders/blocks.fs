#version 330 core

in vec2 v_textCoord;
in float v_blinkFactor;


uniform sampler2D u_texture;
uniform vec3      u_blinkColor = vec3(1.0, 1.0, 1.0);

out vec4 FragColor;

void main() {
  FragColor = mix(texture(u_texture, v_textCoord), vec4(u_blinkColor, 1), v_blinkFactor);
}
