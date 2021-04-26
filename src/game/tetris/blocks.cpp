#include "blocks.h"

#define BLOCK_TEXTURE_PADDING   8.0f/128.0f
#define BLOCK_TEXTURE_SIZE     32.0f/128.0f

void createBlockQuad(std::array<BlockVertex, 4>& vertices, std::array<uint32_t, 6>& indices) {
  vertices[0] = { { 0.25f, 0.25f }, { BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE } };
  vertices[1] = { { 0.25f, 0.00f }, { BLOCK_TEXTURE_SIZE, 0.00f } };
  vertices[2] = { { 0.00f, 0.00f }, { 0.00f, 0.00f } };
  vertices[3] = { { 0.00f, 0.25f }, { 0.00f, BLOCK_TEXTURE_SIZE } };

  indices[0] = 0; indices[1] = 1; indices[2] = 3;
  indices[3] = 1; indices[4] = 2; indices[5] = 3;
}

BlocksMaterial::BlocksMaterial() {

}

void BlocksMaterial::init() {
  TextureCreateParams textureParams;
  textureParams.filePath = "textures/blocks.png";
  _texture = Texture::Create(textureParams);

  ShaderCreateParams shaderParams;
  shaderParams.name = "blocks";
  shaderParams.vertexShaderPath = "shaders/blocks.vs";
  shaderParams.fragmentShaderPath = "shaders/blocks.fs";
  _shader = Shader::Create(shaderParams);
  _shader->use();

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; ++j) {
      const int index = (i*3) + j;

      if (index < BlockId_Count) {
        std::string name = "u_blockOffsets[" + std::to_string(index) + "]";
        glm::vec2 offset;
        offset.s = ((j+1)*BLOCK_TEXTURE_PADDING) + ((j)*BLOCK_TEXTURE_SIZE);
        offset.t = ((3-i)*BLOCK_TEXTURE_PADDING) + ((2-i)*BLOCK_TEXTURE_SIZE);

        _shader->setUniformVec2(name.c_str(), offset);
      }
    }
  }
}
