#pragma once

#include "system/graphics/buffers.h"
#include "system/render_device.h"

#include "blocks.h"

class Tetromino {
private:
  enum {
    FrameCount = 4,
  };

  struct Shape {
    static Shape GetShape(int idx);
    std::array<uint8_t, 16> data[Tetromino::FrameCount];
  };

public:
  Tetromino();

  void init(float size, BlocksMaterialRef material);

  void randomize();
  void rotate();
  void setPosition(const glm::vec2& pos);
  void render(RenderDevice& renderDevice);

private:
  BlocksMaterialRef _material;
  VertexBufferRef _quad;
  VertexBufferRef _instanceData;
  VertexArrayRef  _vertexData;

  Shape     _shape;
  glm::vec2 _position = { 0.0f, 0.0f };
  float     _size = 1.0f;
  uint8_t   _id = BlockId_Purple;
  uint8_t   _frameId = 0;
  uint8_t   _updateVertexData = false;
};
