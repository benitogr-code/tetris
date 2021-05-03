#pragma once

#include "renderer.h"

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
  Tetromino(float blockSize);

  void randomize();

  void rotate();
  void setPosition(const glm::vec2& pos);

  void getBlockCoordinates(const glm::ivec2& offset, std::vector<glm::ivec2>& coords) const;
  void getBlockCoordinatesAfterRotation(const glm::ivec2& offset, std::vector<glm::ivec2>& coords) const;

  void render(Renderer& renderer);

private:
  Shape      _shape;
  glm::vec2  _position = { 0.0f, 0.0f };
  float      _blockSize = 1.0f;
  BlockId    _blockId = BlockId_Purple;
  uint32_t   _frameId = 0;
};
