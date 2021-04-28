#include "tetromino.h"

#include <glad/glad.h>

Tetromino::Tetromino() {

}

void Tetromino::init(BlocksMaterialRef material) {
  _material = material;

  std::array<BlockVertex, 4> vertices;
  std::array<uint32_t, 6> indices;
  createBlockQuad(0.25f, vertices, indices);

  _quad = VertexBuffer::Create(
    vertices.data(),
    sizeof(BlockVertex)*4,
    BufferLayout({
      { BufferItemType::Float2, "position" },
      { BufferItemType::Float2, "textureCoords" }
    })
  );

  _instanceData = VertexBuffer::Create(
    sizeof(BlockInstance)*4,
    BufferLayout({
      { BufferItemType::Float2, "translation" },
      { BufferItemType::Int, "blockId" },
    })
  );
  _instanceData->setFlag(VertexBuffer::Flag_Instance);

  _vertexData = VertexArray::Create();
  _vertexData->addVertextBuffer(_quad);
  _vertexData->addVertextBuffer(_instanceData);
  _vertexData->setIndexBuffer(
    IndexBuffer::Create(indices.data(), sizeof(uint32_t)*indices.max_size())
  );
}

void Tetromino::render(RenderDevice& renderDevice) {
  std::array<BlockInstance, 4> instances;
  instances[0] = { { -0.375f,  0.0f }, BlockId_Red };
  instances[1] = { { -0.125f,  0.0f }, BlockId_Purple };
  instances[2] = { {  0.125f,  0.0f }, BlockId_Red };
  instances[3] = { { -0.125f, -0.25f }, BlockId_Cyan };

  _instanceData->uploadData(instances.data(), sizeof(BlockInstance)*4);

  _material->getTexture()->bind();
  renderDevice.drawInstanced(_vertexData, _material->getShader(), 4);
}
