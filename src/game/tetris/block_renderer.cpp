#include "block_renderer.h"

#include <glad/glad.h>

#define MAX_BLOCKS 1024
#define BLOCK_TEXTURE_PADDING   8.0f/128.0f
#define BLOCK_TEXTURE_SIZE     32.0f/128.0f

BlockRenderer::BlockRenderer(float blockSize) {
  _blocks.reserve(MAX_BLOCKS);
  _blockSize = blockSize;
  _viewProjection = glm::mat4x4(1.0f);
}

void BlockRenderer::init() {
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

  std::array<BlockVertex, 4> vertices;
  vertices[0] = { glm::vec2(_blockSize, _blockSize), glm::vec2(BLOCK_TEXTURE_SIZE, BLOCK_TEXTURE_SIZE) };
  vertices[1] = { glm::vec2(_blockSize, 0.0f), glm::vec2(BLOCK_TEXTURE_SIZE, 0.0f) };
  vertices[2] = { glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f) };
  vertices[3] = { glm::vec2(0.0f, _blockSize), glm::vec2(0.0f, BLOCK_TEXTURE_SIZE) };
  const std::array<uint32_t, 6> indices = {
    0, 1, 3,
    1, 2, 3
  };

  auto vbQuad = VertexBuffer::Create(
    vertices.data(),
    sizeof(BlockVertex)*4,
    BufferLayout({
      { BufferItemType::Float2, "position" },
      { BufferItemType::Float2, "textureCoords" }
    })
  );

  _vbBlocks = VertexBuffer::Create(
    sizeof(BlockInstance)*MAX_BLOCKS,
    BufferLayout({
      { BufferItemType::Float2, "translation" },
      { BufferItemType::Int, "blockId" },
    })
  );
  _vbBlocks->setFlag(VertexBuffer::Flag_Instance);

  _va = VertexArray::Create();
  _va->addVertextBuffer(vbQuad);
  _va->addVertextBuffer(_vbBlocks);
  _va->setIndexBuffer(
    IndexBuffer::Create(indices.data(), sizeof(uint32_t)*indices.max_size())
  );
}

void BlockRenderer::beginFrame(const glm::mat4x4& viewProjection) {
  _viewProjection = viewProjection;
  _blocks.clear();
}

void BlockRenderer::endFrame() {
  if (_blocks.size() == 0)
    return;

  auto blockCount = _blocks.size();
  _vbBlocks->uploadData(_blocks.data(), sizeof(BlockInstance)*blockCount);

  _texture->bind();
  _shader->use();
  _shader->setUniformMatrix4("u_viewProjection", _viewProjection);
  _va->bind();
  glDrawElementsInstanced(GL_TRIANGLES, _va->indexCount(), GL_UNSIGNED_INT, nullptr, blockCount);
  _va->unbind();
}

void BlockRenderer::drawBlock(const glm::vec2& position, BlockId id) {
  if (_blocks.size() >= MAX_BLOCKS)
    return;

  _blocks.push_back({ position, (uint32_t)id });
}
