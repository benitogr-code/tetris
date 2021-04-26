#pragma once

#include "system/graphics/buffers.h"

#include "blocks.h"

class Tetromino {
public:
  Tetromino();

  void init(BlocksMaterialRef material);
  void render(const glm::mat4x4& viewProjection);

private:
  BlocksMaterialRef _material;
  VertexBufferRef _quad;
  VertexBufferRef _instanceData;
  VertexArrayRef  _vertexData;
};
