#pragma once

#include "system/graphics/buffers.h"
#include "system/graphics/shader.h"

#include "blocks.h"

class Tetromino {
public:
  Tetromino();

  void init();
  void render(const BlockAtlas& atlas, const glm::mat4x4& viewProjection);

private:
  ShaderRef _shader;
  VertexBufferRef _quad;
  VertexBufferRef _instanceData;
  VertexArrayRef  _vertexData;
};
