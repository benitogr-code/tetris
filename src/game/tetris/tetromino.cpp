#include "tetromino.h"

#include <glad/glad.h>

struct Vertex {
  glm::vec2 position;
  glm::vec2 textureCoords;
};

struct Instance {
  glm::vec2 translation;
  glm::vec2 textureOffset;
};

Tetromino::Tetromino() {

}

void Tetromino::init() {
  std::array<Vertex, 4> quadVertices;
  quadVertices[0] = { { 0.25f, 0.25f }, { 0.25f, 0.25f } };
  quadVertices[1] = { { 0.25f, 0.00f }, { 0.25f, 0.00f } };
  quadVertices[2] = { { 0.00f, 0.00f }, { 0.00f, 0.00f } };
  quadVertices[3] = { { 0.00f, 0.25f }, { 0.00f, 0.25f } };
  std::array<uint32_t, 6> quadIndices = { 0, 1, 3, 1, 2, 3};

  _quad = VertexBuffer::Create(
    quadVertices.data(),
    sizeof(Vertex)*4,
    BufferLayout({
      { BufferItemType::Float2, "position" },
      { BufferItemType::Float2, "textureCoords" }
    })
  );

  _instanceData = VertexBuffer::Create(
    sizeof(Instance)*4,
    BufferLayout({
      { BufferItemType::Float2, "translation" },
      { BufferItemType::Float2, "textureOffset" },
    })
  );
  _instanceData->setFlag(VertexBuffer::Flag_Instance);

  _vertexData = VertexArray::Create();
  _vertexData->addVertextBuffer(_quad);
  _vertexData->addVertextBuffer(_instanceData);
  _vertexData->setIndexBuffer(
    IndexBuffer::Create(quadIndices.data(), sizeof(uint32_t)*quadIndices.max_size())
  );

  ShaderCreateParams params;
  params.name = "blocks";
  params.vertexShaderPath = "shaders/blocks.vs";
  params.fragmentShaderPath = "shaders/blocks.fs";
  _shader = Shader::Create(params);
}

void Tetromino::render(const BlockAtlas& atlas, const glm::mat4x4& viewProjection) {
  std::array<Instance, 4> instances;
  auto block = atlas.getBlockInfo(BlockId_Red);

  instances[0] = { { -0.375f,  0.0f }, block.offset };
  instances[1] = { { -0.125f,  0.0f }, block.offset };
  instances[2] = { {  0.125f,  0.0f }, block.offset };
  instances[3] = { { -0.125f, -0.25f }, block.offset };

  _instanceData->uploadData(instances.data(), sizeof(Instance)*4);

  atlas.getTexture()->bind();
  _shader->use();
  _shader->setUniformMatrix4("u_viewProjection", viewProjection);
  _vertexData->bind();
  glDrawElementsInstanced(GL_TRIANGLES, _vertexData->indexCount(), GL_UNSIGNED_INT, nullptr, 4);

  _vertexData->unbind();
}
