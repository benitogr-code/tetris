#pragma once

#include "block_renderer.h"

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

  void randomize();
  void rotate();
  void setPosition(const glm::vec2& pos);
  void render(BlockRenderer& renderer);

private:
  Shape     _shape;
  glm::vec2 _position = { 0.0f, 0.0f };
  BlockId   _blockId = BlockId_Purple;
  uint32_t  _frameId = 0;
};
