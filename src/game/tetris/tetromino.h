#pragma once

#include "system/graphics/buffers.h"
#include "system/render_device.h"

#include "blocks.h"

class Tetromino {
public:
  Tetromino();

  void init(BlocksMaterialRef material);
  void render(RenderDevice& renderDevice);

private:
  BlocksMaterialRef _material;
  VertexBufferRef _quad;
  VertexBufferRef _instanceData;
  VertexArrayRef  _vertexData;
};
